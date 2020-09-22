#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <thread>
#include <filesystem>
#include <boost/algorithm/string.hpp>

#include "waiter/Waiter.h"
#include "pathPool/PathPool.h"
#include "authentication/authentication.h"
#include "jobRequestQueue/JobRequestQueue.h"
#include "ChecksumStorage/ChecksumStorage.h"

#include "../common/messages/socket_utils.h"
#include "../common/messages/AuthenticationRequest.pb.h"
#include "../common/messages/AuthenticationResponse.pb.h"

std::optional<std::string> doAuthentication(boost::asio::ip::tcp::socket& );
std::shared_ptr<PathPool> loadWorkspace(boost::asio::ip::tcp::socket&, std::string&);
void serveJobRequest(boost::asio::ip::tcp::socket&, std::string&, JobRequestQueue&);
void sendResponses(boost::asio::ip::tcp::socket&,  JobRequestQueue&);
void cleanFileSystem(const std::string& path);

int main(int argc, char* argv[]) {

    //TODO see how it works    GOOGLE_PROTOBUF_VERIFY_VERSION;
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

            if(username.has_value()){
                std::cout<< "Username: " << username.value() << std::endl;

                std::shared_ptr<PathPool> poolItem = loadWorkspace(s, username.value());
                if(poolItem->isValid()){
                    switch (poolItem->getRestore()) {
                        case true:
                            //TODO implement restore
                            break;
                        case false:
                            std::string path= poolItem->getPath();
                            JobRequestQueue queue{};
                            std::thread responder{sendResponses, std::ref(s), std::ref(queue)};
                            while(true)
                                serveJobRequest(s, path, queue);

                    }

                }else{
                    std::cout<<username.value()<<" failed to connect to the workspace"<<std::endl;
                }

            } else std::cout << "Login failed (server)" << std::endl;



            return;
        }, std::move(socket)};
        thread.detach();

    }


//    return 1;
}

std::optional<std::string> doAuthentication(boost::asio::ip::tcp::socket& s){

    BackupPB::AuthenticationRequest authenticationRequest;
    BackupPB::AuthenticationResponse authenticationResponse;
    std::optional<std::string> username;

    try{
        authenticationRequest = readFromSocket<BackupPB::AuthenticationRequest>(s);
    } catch(std::exception& e) {
        std::cerr<< e.what() << std::endl;
        return std::nullopt;
    }

    if(!authenticate(authenticationRequest.username(), authenticationRequest.password())){
        //std::cerr << "Login failed" << std::endl;
        authenticationResponse.set_status(BackupPB::AuthenticationResponse_Status_FAIL);
        username = std::nullopt;
    } else {
        authenticationResponse.set_status(BackupPB::AuthenticationResponse_Status_OK);
        username = authenticationRequest.username();
    }

    try{
        writeToSocket(s, authenticationResponse);
    } catch(std::exception& e){
        std::cerr << e.what() << std::endl;
        return std::nullopt;
    }

    return username;
}

std::shared_ptr<PathPool> loadWorkspace(boost::asio::ip::tcp::socket& s, std::string& username){
    //read message with path and machineID
    //if (!RESTORE)
        //compute server path

        //create pathPool with corresponding path

            //error response [TO CLIENT] and return inValid PathPool

        //cleanFileSystem()
        //compute metadata and send back to client



    //else
        // send list of all workspaces
        // wait response
        // create PathPool for folder#
        // update entry (if new workspace not exists)
        // cleanFileSystem()



    //return pathPool

    return nullptr;
}


void serveJobRequest(boost::asio::ip::tcp::socket& socket, std::string& serverPath, JobRequestQueue& queue){
    //get job request

    //switch Action

        //add_file && update -> receive file, save into temporary and put into queue

        //add_dir -> put in queue


        //delete ->  put in queue

}

void sendResponses(boost::asio::ip::tcp::socket& socket,  JobRequestQueue& queue){
    while(true){
        //pick a job from queue
        //switch Action

            //add_file && update -> computeChecksum [AND CACHE], move temporary file and generate response

            //add_dir -> create dir and respond

            //delete -> delete file  [AND IN CACHE TOO] or directory [CLEAR CACHE IN SUBFOLDERS] respond
    }
}

bool restore(boost::asio::ip::tcp::socket& socket, std::shared_ptr<PathPool> pool){
    //TODO implement
    return true;
}

void cleanFileSystem(const std::string& path){
    for(std::filesystem::directory_entry element : std::filesystem::recursive_directory_iterator(path)) {
        //scan recursively all files in path
        std::string file_path{element.path().string()};
        if(element.is_regular_file() && boost::algorithm::ends_with(element.path().string(), TMP_EXTENSION)) {
            boost::algorithm::erase_last(file_path, std::string{TMP_EXTENSION});

            std::filesystem::directory_entry old{file_path};
            // if (.tmp is present && normal !present)
            if(!old.exists())
                updateChecksum(file_path);
            else
                // if (both presents)
                //keep older
                std::filesystem::remove(file_path+TMP_EXTENSION);
        }
    }
}