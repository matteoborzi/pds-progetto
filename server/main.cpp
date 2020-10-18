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
#include "jobRequestQueue/jobManager.h"


bool restore(boost::asio::ip::tcp::socket&, const std::string&);

int main(int argc, char* argv[]) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;
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
                            /* TODO check restore return */
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

