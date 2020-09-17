#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <thread>

#include "Configuration/Configuration.h"
#include "job/JobQueue.h"
#include "FileWatcher/watcher.h"

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

    //TODO command line parameter checks
    std::string confFile{argv[1]};
    std::optional<Configuration> configuration = Configuration::getConfiguration(confFile);
    //TODO checks on correct configuration

    Configuration conf= configuration.value();

    boost::asio::io_context io_service;

    boost::asio::ip::tcp::socket socket(io_service);

    socket.connect( boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string(
            conf.getIpAddress()), conf.getPort()));
    //TODO checks on connection


    login(socket,conf.getUsername(), conf.getPassword());
    //TODO checks on login response

    chooseWorkspace(socket, conf.getMachineID(), conf.getPath());
    //TODO checks on workspace selection

    JobQueue queue{};
    std::thread sender{sendData, std::ref(socket), std::ref(queue)},
        receiver{receiveData, std::ref(socket), std::ref(queue)};

    watch(queue);
    return 0;
}

bool login(boost::asio::ip::tcp::socket& socket, std::string& username, std::string& password){
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

