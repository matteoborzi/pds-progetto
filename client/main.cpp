#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <thread>
#include <filesystem>

#include "Configuration/Configuration.h"
#include "job/JobQueue.h"
#include "FileWatcher/watcher.h"

#include "../common/messages/socket_utils.h"
#include "Configuration/file_util.h"
#include "communicationProtocol/initialization.h"
#include "communicationProtocol/dataManagement.h"
#include "communicationProtocol/restore.h"

#define MAX_CONNECTION_ATTEMPTS 3
#define CONNECTION_RETRY_PERIOD 2 //seconds to wait before a reconnection


int main(int argc, char *argv[]) {

    if ((argc != 2 && argc != 3) || (argc == 3 && std::string{argv[2]} != "--r")) {
        std::cerr << "Wrong parameters. Usage: client_executable configuration_file [--r]" << std::endl;
        return 1;
    }

    std::string confFile{argv[1]};
    std::optional<Configuration> configuration = Configuration::getConfiguration(confFile);

    if (!configuration.has_value()) {
        std::cerr << "Impossible to load configuration" << std::endl;
        return 2;
    }
    Configuration conf = configuration.value();

    boost::asio::io_context io_service;
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket(io_service, ssl_context);
    boost::asio::ip::tcp::resolver resolver(io_service);


    //ssl_context.load_verify_file("../../common/cert/server.pem");
    ssl_context.set_verify_mode(boost::asio::ssl::verify_peer);
    //ssl_context.set_verify_callback(boost::asio::ssl::rfc2818_verification("127.0.0.1"));

    auto endpoints = resolver.resolve(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(
            conf.getIpAddress()), conf.getPort()));


    int attempts = MAX_CONNECTION_ATTEMPTS;
    bool connected = true;
    do {
        try {
            boost::asio::connect(socket.next_layer(), endpoints);
            socket.handshake(boost::asio::ssl::stream_base::client);

        } catch (boost::system::system_error &e) {

            attempts--;
            connected= false;

            if(attempts==0) {

                std::cerr << "Impossible to connect to the server" << std::endl;
                return 3;
            }
            std::cerr<<"An attempt to connect to the server failed, retrying in "<<CONNECTION_RETRY_PERIOD<<" second(s)"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(CONNECTION_RETRY_PERIOD));
        }
    }while(!connected);

    try {
        if (argc == 3 && !std::filesystem::is_empty(std::filesystem::path{conf.getPath()})) {
            std::cerr << "Error: root chosen for restore is not empty" << std::endl;
            return 4;
        }
    }catch(...){
        std::cerr<<"Impossible to determine whether the selected folder for restore is empty or not"<<std::endl;
        return 4;
    }

    if (!login(socket, conf.getUsername(), conf.getPassword())) {
        std::cerr << "Error during authentication" << std::endl;
        return 5;
    }

    std::cout << "Successful login" << std::endl;


    if (argc == 3) {
        if (!restore(socket, conf.getMachineID(), conf.getPath())) {
            std::cerr << "Error during file restore" << std::endl;
            return 6;
        } 
        else{
        	std::cout << "Terminating program..." << std::endl;	
        	return 0;
        }
    }
    if (!chooseWorkspace(socket, conf.getMachineID(), conf.getPath())) {
        std::cerr << "Error during workspace choice" << std::endl;
        return 7;
    }

    std::atomic_bool termination=false;
    JobQueue queue{};
    std::thread sender{sendData, std::ref(socket), std::ref(queue), std::ref(termination)},
            receiver{receiveData, std::ref(socket), std::ref(queue), std::ref(termination)};
    try {
        watch(queue, termination);
    } catch (std::exception& e) {
        std::cerr<<e.what()<<std::endl;

        termination= true; //signaling other thread to close

        //closing the socket (receiver thread will get an exception and terminate)
        close_socket(socket);

        //notifying waiting sender thread if blocked
        queue.addIfEmpty(Job::terminationJob());
    }
    std::cout<<"Terminating the execution...\n"<<std::flush;

    sender.join();
    receiver.join();

    return 0;
}



