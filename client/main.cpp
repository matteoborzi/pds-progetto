#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <thread>
#include <filesystem>
#include "../common/messages/JobRequest.pb.h"


#include "Configuration/Configuration.h"
#include "job/JobQueue.h"
#include "FileWatcher/watcher.h"

#include "../common/messages/socket_utils.h"
#include "../common/messages/file_utils.h"
#include "../common/job_utils.h"

#include "../common/messages/AuthenticationRequest.pb.h"
#include "../common/messages/AuthenticationResponse.pb.h"
#include "../common/messages/DirectoryEntryMessage.pb.h"
#include "../common/messages/Workspace.pb.h"
#include "../common/messages/MetaInfo.pb.h"
#include "../common/messages/JobResponse.pb.h"
#include "../common/messages/RestoreResponse.pb.h"


#include "../common/Checksum.h"
#include "DirectoryStructure/utils.h"
#include "Configuration/file_util.h"
#include "../common/messages/AvailableWorkspaces.pb.h"
#include "communicationProtocol/initialization.h"
#include "communicationProtocol/dataManagement.h"
#include "communicationProtocol/restore.h"


int main(int argc, char *argv[]) {
//    boost::asio::io_context io_service;
////socket creation
//    boost::asio::ip::tcp::socket socket(io_service);
////connection
//    socket.connect( boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 8080 ));
//    return 2;
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

    boost::asio::ip::tcp::socket socket(io_service);
    try {
        socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(
                conf.getIpAddress()), conf.getPort()));
    } catch (boost::system::system_error &e) {
        //TODO evaluate a retry
        std::cerr << "Impossible to connect to the server" << std::endl;
        return 3;
    }

    //TODO eventually catch exception thrown by path constructor
    if(argc==3 && !std::filesystem::is_empty(std::filesystem::path{conf.getPath()}) ){
        std::cerr << "Error: root chosen for restore is not empty" << std::endl;
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
        //TODO see if it is necessary to send some messages to the server
        return 7;
    }


    JobQueue queue{};
    std::thread sender{sendData, std::ref(socket), std::ref(queue)},
            receiver{receiveData, std::ref(socket), std::ref(queue)};

    watch(queue);
    return 0;
}



