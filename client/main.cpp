#include <iostream>
#include <thread>
#include <filesystem>

#include "Configuration/Configuration.h"
#include "Configuration/file_util.h"
#include "job/JobQueue.h"
#include "FileWatcher/watcher.h"

#include "communicationProtocol/initialization.h"
#include "communicationProtocol/dataManagement.h"
#include "communicationProtocol/restore.h"
#include "communicationProtocol/connection_utils.h"

#include "../common/messages/socket_utils.h"

#define MAX_CONNECTION_ATTEMPTS 3
#define CONNECTION_RETRY_PERIOD 2 //seconds to wait before a reconnection

int main(int argc, char *argv[]) {

    //parameter check
    //  usage: <conf_file_path> [--r]
    if ((argc != 2 && argc != 3) || (argc == 3 && std::string{argv[2]} != "--r")) {
        std::cerr << "Wrong parameters. Usage: client_executable configuration_file [--r]" << std::endl;
        return 1;
    }

    //loading configuration file
    std::string confFile{argv[1]};
    std::optional<Configuration> configuration = Configuration::getConfiguration(confFile);

    if (!configuration.has_value()) {
        std::cerr << "Impossible to load configuration" << std::endl;
        return 2;
    }
    Configuration conf = configuration.value();

    //setting up connection and SSL parameters
    boost::asio::io_context io_service;
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
    ssl_context.set_verify_mode(boost::asio::ssl::verify_peer);
    ssl_context.load_verify_file("../cert/server.cert.pem");
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket(io_service, ssl_context);

    //resolving server endpoint
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(
                    conf.getIpAddress()), conf.getPort());

    //performing the connection
    int attempts = MAX_CONNECTION_ATTEMPTS;
    bool connected = true;
    do {
        //trying to connect
        try {
            custom_connect(socket.next_layer(), endpoint, std::chrono::seconds(10), io_service);

        } catch (std::system_error &e) {

            attempts--;
            connected= false;

            if(attempts==0) {
                //max number of attempts exceeded
                std::cerr << "Impossible to connect to the server" << std::endl;
                return 3;
            }
            std::cerr<<"An attempt to connect to the server failed, retrying in "<<CONNECTION_RETRY_PERIOD<<" second(s)"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(CONNECTION_RETRY_PERIOD));
            continue;
        }
        try{
            custom_handshake(socket,std::chrono::seconds(15), io_service);
        } catch (std::system_error &e) {
            socket.next_layer().close();
            std::cerr << "Error in performing handshake: " << e.what() << std::endl;
            return 3;
        }
    }while(!connected);

    //performing checks for restore
    try {
        if (argc == 3 && !std::filesystem::is_empty(std::filesystem::path{conf.getPath()})) {
            std::cerr << "Error: root chosen for restore is not empty" << std::endl;
            return 4;
        }
    }catch(...){
        std::cerr<<"Impossible to determine whether the selected folder for restore is empty or not"<<std::endl;
        return 4;
    }

    //performing authentication to server
    if (!login(socket, conf.getUsername(), conf.getPassword())) {
        std::cerr << "Error during authentication" << std::endl;
        return 5;
    }

    std::cout << "Successful login" << std::endl;


    if (argc == 3) {
        //performing restore
        if (!restore(socket, conf.getMachineID(), conf.getPath())) {
            std::cerr << "Error during file restore" << std::endl;
            return 6;
        } 
        else{
            //restore ended correctly
        	std::cout << "Terminating program..." << std::endl;	
        	return 0;
        }
    }

    //sending data to select the workspace to use
    if (!chooseWorkspace(socket, conf.getMachineID(), conf.getPath())) {
        std::cerr << "Error during workspace choice" << std::endl;
        return 7;
    }


    std::atomic_bool termination=false;
    JobQueue queue{}; //the Queue that will accept jobs to deliver to the server

    //configuring thread to manage backup system
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



