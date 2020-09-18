#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <thread>
#include "../common/messages/JobRequest.pb.h"


#include "Configuration/Configuration.h"
#include "job/JobQueue.h"
#include "FileWatcher/watcher.h"

#include "../common/messages/socket_utils.h"

#include "../common/messages/AuthenticationRequest.pb.h"
#include "../common/messages/JobRequest.pb.h"
#include "../common/messages/AuthenticationResponse.pb.h"

bool login(boost::asio::ip::tcp::socket&, std::string&, std::string& );
bool chooseWorkspace(boost::asio::ip::tcp::socket&, std::string&, std::string& );
void sendData(boost::asio::ip::tcp::socket&, JobQueue& );
void receiveData(boost::asio::ip::tcp::socket&, JobQueue& );

int main(int argc, char* argv[]) {

//    boost::asio::io_context io_service;
////socket creation
//    boost::asio::ip::tcp::socket socket(io_service);
////connection
//    socket.connect( boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 8080 ));
//    return 2;
    if( ( argc != 2 && argc != 3)  || (argc==3 && std::string{argv[2]}!="--r")){
        std::cerr<<"Wrong parameters. Usage: client_executable configuration_file [--r]"<<std::endl;
        return 1;
    }

    std::string confFile{argv[1]};
    std::optional<Configuration> configuration = Configuration::getConfiguration(confFile);

    if(!configuration.has_value()){
        std::cerr<<"Impossible to load configuration"<<std::endl;
        return 2;
    }
    Configuration conf= configuration.value();

    boost::asio::io_context io_service;

    boost::asio::ip::tcp::socket socket(io_service);
    try {
        socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(
                conf.getIpAddress()), conf.getPort()));
    } catch(boost::system::system_error& e){
        //TODO evaluate a retry
        std::cerr<<"Impossible to connect to the server"<<std::endl;
        return 3;
    }



    if(!login(socket,conf.getUsername(), conf.getPassword())){
        std::cerr<<"Error during authentication"<<std::endl;
        return 4;
    }


    if(!chooseWorkspace(socket, conf.getMachineID(), conf.getPath())){
        std::cerr<<"Error during workspace choice"<<std::endl;
        //TODO see if it is necessary to send some messages to the server
        return 5;
    }


    JobQueue queue{};
    std::thread sender{sendData, std::ref(socket), std::ref(queue)},
        receiver{receiveData, std::ref(socket), std::ref(queue)};

    watch(queue);
    return 0;
}

bool login(boost::asio::ip::tcp::socket& socket, std::string& username, std::string& password){
    AuthenticationRequest req;

    req.set_username(username);
    req.set_password(password);

    try{
        writeToSocket(socket, req);
    } catch (std::exception& e) {
        std::cerr<<e.what()<<std::endl;
        return false;
    }

    AuthenticationResponse response;
    try{
        response = readFromSocket<AuthenticationResponse>(socket);
    }catch (std::exception& e) {
        std::cerr<<e.what()<<std::endl;
        return false;
    }
    if(response.status()!=AuthenticationResponse_Status_OK)
        return false;
    return true;
}

bool chooseWorkspace(boost::asio::ip::tcp::socket& socket, std::string& machineId, std::string& path ){
    //send workspace choice

    //load DirectoryStructure on response
    return true;
}

void sendData(boost::asio::ip::tcp::socket& socket, JobQueue& queue){
    while(true){
        //get a job

        //choose what to do
            //in case of add and update, check if file/folder still exists in file system and directory structure


        //compute checksum (if needed)

        //send data

        //update checksum (if needed) in Directory structure
    }
}

void receiveData(boost::asio::ip::tcp::socket& socket, JobQueue& queue){
    while(true){
        //receive data from socket

        //if checksum is present and file still exists in directory structure compute equals
        //if it does not exists anymore do nothing (do not retry)
        //otherwise retry or setConcluded job
    }
}

