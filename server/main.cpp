#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <thread>
#include <filesystem>
#include <boost/algorithm/string.hpp>

#include "waiter/Waiter.h"
#include "pathPool/PathPool.h"
#include "authentication/authentication.h"
#include "jobRequestQueue/JobRequestQueue.h"
#include "Workspace/workspace_utils.h"
#include "ChecksumStorage/ChecksumStorage.h"

#include "../common/messages/socket_utils.h"
#include "../common/messages/file_utils.h"
#include "../common/messages/AuthenticationRequest.pb.h"
#include "../common/messages/AuthenticationResponse.pb.h"
#include "../common/messages/Workspace.pb.h"
#include "../common/messages/DirectoryEntryMessage.pb.h"
#include "../common/messages/MetaInfo.pb.h"
#include "../common/messages/MachinePath.pb.h"
#include "../common/messages/AvailableWorkspaces.pb.h"
#include "../common/messages/RestoreResponse.pb.h"
#include "../common/messages/JobRequest.pb.h"
#include "../common/messages/JobResponse.pb.h"
#include "Workspace/load.h"


void serveJobRequest(boost::asio::ip::tcp::socket&, std::string&, JobRequestQueue&);
void sendResponses(boost::asio::ip::tcp::socket&,  JobRequestQueue&, const std::string&);

bool restore(boost::asio::ip::tcp::socket&, const std::string&);

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
                    std::string path= poolItem->getPath();
                    switch (poolItem->getRestore()) {
                        case true:
                            //TODO check restore return 
                            restore(s, path);
                            break;
                        case false:

                            JobRequestQueue queue{};
                            std::thread responder{sendResponses, std::ref(s), std::ref(queue), std::cref(path)};
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






void serveJobRequest(boost::asio::ip::tcp::socket& socket, std::string& serverPath, JobRequestQueue& queue){
    //get job request
    BackupPB::JobRequest req= readFromSocket<BackupPB::JobRequest>(socket);
    //removing initial /
    std::string path{serverPath+req.path().substr(1,req.path().size() )};

    if(req.pbaction()==BackupPB::JobRequest_PBAction_ADD_FILE ||req.pbaction()==BackupPB::JobRequest_PBAction_UPDATE )
        //add_file && update -> receive file, save into temporary and put into queue
        receiveFile(socket, path+TMP_EXTENSION, req.size());
    else if(req.pbaction()==BackupPB::JobRequest_PBAction_ADD_DIRECTORY)
        std::filesystem::create_directories(path);
    //saving in queue
    queue.enqueueJobRequest(req);

}

void sendResponses(boost::asio::ip::tcp::socket& socket,  JobRequestQueue& queue, const std::string& base_path){
    while(true){
        BackupPB::JobRequest request = queue.dequeueJobRequest();
        BackupPB::JobResponse response{};
        response.set_path(request.path());

        std::string complete_path{base_path+request.path().substr(1,request.path().size())};
        switch(request.pbaction()){
            case BackupPB::JobRequest_PBAction_ADD_FILE :
            case BackupPB::JobRequest_PBAction_UPDATE :
                if(!updateChecksum(complete_path)){
                    response.set_status(BackupPB::JobResponse_Status_FAIL);
                }
                else{
                    std::optional<std::string> checksum = getChecksum(complete_path);
                    if(!checksum.has_value())
                        response.set_status(BackupPB::JobResponse_Status_FAIL);
                    else {
                        response.set_status(BackupPB::JobResponse_Status_OK);
                        response.set_checksum(checksum.value());
                    }
                }
                break;
            case BackupPB::JobRequest_PBAction_ADD_DIRECTORY:
                response.set_status(BackupPB::JobResponse_Status_OK);
                break;
            case BackupPB::JobRequest_PBAction_DELETE :
                if(!deleteFolderRecursively(complete_path))
                    response.set_status(BackupPB::JobResponse_Status_FAIL);
                else
                    response.set_status(BackupPB::JobResponse_Status_OK);
                break;
        }

        try{
            writeToSocket(socket, response);
        }
        catch(std::exception& e){
            throw e;
        }
    }
}

bool restore(boost::asio::ip::tcp::socket& socket, const std::string& path) {
    for (std::filesystem::directory_entry entry : std::filesystem::recursive_directory_iterator(path)) {
        BackupPB::JobRequest request{};
        if (entry.is_directory())
            request.set_pbaction(BackupPB::JobRequest_PBAction_ADD_DIRECTORY);
        else if (entry.is_regular_file()) {
            request.set_pbaction(BackupPB::JobRequest_PBAction_ADD_FILE);
            request.set_size(entry.file_size());
        }
        std::string path_to_send = entry.path();
        boost::algorithm::erase_first(path_to_send, path);
        request.set_path(path_to_send);

        try {
            writeToSocket(socket, request);
            if (request.pbaction() == BackupPB::JobRequest_PBAction_ADD_FILE)
                sendFile(socket, entry.path(), request.size());
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }
    BackupPB::JobRequest end{};
    end.set_pbaction(BackupPB::JobRequest_PBAction_END_RESTORE);
    end.set_path(" ");
    try {
        writeToSocket(socket, end);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

