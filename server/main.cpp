#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <thread>

#include "waiter/Waiter.h"
#include "pathPool/PathPool.h"
#include "authentication/authentication.h"
#include "jobRequestQueue/JobRequestQueue.h"

#include "../common/messages/socket_utils.h"
#include "../common/messages/AuthenticationRequest.pb.h"
#include "../common/messages/AuthenticationResponse.pb.h"

std::optional<std::string> doAuthentication(boost::asio::ip::tcp::socket& );
std::shared_ptr<PathPool> loadWorkspace(boost::asio::ip::tcp::socket&, std::string&);
void serveJobRequest(boost::asio::ip::tcp::socket&, std::string&, JobRequestQueue&);
void sendResponses(boost::asio::ip::tcp::socket&,  JobRequestQueue&);

int main(int argc, char* argv[]) {

    int port;

    if(argc < 2) {
        std::cerr<<"Not enough arguments: port_number is missing" << std::endl;
        return 1;
    }

    try{
        port = std::stoi(argv[1]);
    } catch (std::exception& e) {
        std::cerr<<"Invalid port argument: not a number"<<std::endl;
        return 2;
    }

    boost::asio::io_context my_context;
    boost::asio::ip::tcp::acceptor acceptor(my_context);

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();
    std::cout<<"I'm listening"<<std::endl;

    while(true) {

        std::shared_ptr<Waiter> w=std::make_shared<Waiter>();

        boost::asio::ip::tcp::socket socket(my_context);

        acceptor.accept(socket);
        std::cout << "Get a connection" << std::endl;

        std::cout<<"Creating the thread..."<<std::endl;
        std::thread thread{[w](boost::asio::ip::tcp::socket&& s)->void{

            std::optional<std::string> username = doAuthentication(s);
//            if(username.has_value()){
//                std::shared_ptr<PathPool> poolItem = loadWorkspace(s, username.value());
//                if(poolItem->isValid()){
//                    std::string path= poolItem->getPath();
//                    JobRequestQueue queue{};
//                    std::thread responder{sendResponses, std::ref(s), std::ref(queue)};
//                    while(true)
//                        serveJobRequest(s, path, queue);
//                }
//
//            }

            if(username.has_value())
                std::cout<< "Username: " << username.value() << std::endl;
            else std::cout << "Login failed (server)" << std::endl;

            return;
        }, std::move(socket)};
        thread.detach();

    }


//    return 1;
}

std::optional<std::string> doAuthentication(boost::asio::ip::tcp::socket& s){
    //TODO add try block when calling socket_utils functions
    BackupPB::AuthenticationRequest authenticationRequest = readFromSocket<BackupPB::AuthenticationRequest>(s);
    BackupPB::AuthenticationResponse authenticationResponse;
    std::optional<std::string> username;

    if(!authenticate(authenticationRequest.username(), authenticationRequest.password())){
        //std::cerr << "Login failed" << std::endl;
        authenticationResponse.set_status(BackupPB::AuthenticationResponse_Status_FAIL);
        username = std::nullopt;
    } else {
        authenticationResponse.set_status(BackupPB::AuthenticationResponse_Status_OK);
        username = authenticationRequest.username();
    }

    writeToSocket(s, authenticationResponse);

    return username;
}

std::shared_ptr<PathPool> loadWorkspace(boost::asio::ip::tcp::socket& s, std::string& username){
    //read message with path and machineID

    //compute server path

    //create pathPool with corresponding path

        //error response [TO CLIENT] and return inValid PathPool

    //compute metadata and send back to client

    //return pathPool

    return nullptr;
}


void serveJobRequest(boost::asio::ip::tcp::socket& socket, std::string& serverPath, JobRequestQueue& queue){
    //get job request

    //switch Action

        //add_file && update -> receive file, save and put into queue

        //add_dir -> create dir [CREATE FOLDER IN CHECKSUM TOO] and put in queue


        //delete -> delete file and or directory [AND IN CACHE TOO] put in queue

}

void sendResponses(boost::asio::ip::tcp::socket& socket,  JobRequestQueue& queue){
    while(true){
        //pick a job from queue
        //switch Action

            //add_file && update -> computeChecksum [AND CACHE] and generate response

            //add_dir ->respond

            //delete -> respond
    }
}