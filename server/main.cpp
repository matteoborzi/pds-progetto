#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <thread>

#include "waiter/Waiter.h"
#include "pathPool/PathPool.h"
#include "jobRequestQueue/JobRequestQueue.h"

std::optional<std::string> doAuthentication(boost::asio::ip::tcp::socket& );
std::shared_ptr<PathPool> loadWorkspace(boost::asio::ip::tcp::socket&, std::string&);
void serveJobRequest(boost::asio::ip::tcp::socket&, std::string&, JobRequestQueue&);
void sendResponses(boost::asio::ip::tcp::socket&,  JobRequestQueue&);

int main() {

    boost::asio::io_context my_context;

    boost::asio::ip::tcp::acceptor acceptor(my_context);
    //TODO porta da linea di comando
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 8080);
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
            if(username.has_value()){
                std::shared_ptr<PathPool> poolItem = loadWorkspace(s, username.value());
                if(poolItem->isValid()){
                    std::string path= poolItem->getPath();
                    JobRequestQueue queue{};
                    std::thread responder{sendResponses, s, queue};
                    while(true)
                        serveJobRequest(s, path, queue);
                }

            }

            return;
        }, std::move(socket)};
        thread.detach();

    }


    return 1;
}

std::optional<std::string> doAuthentication(boost::asio::ip::tcp::socket& s){
    return std::nullopt;
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