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


bool restore(boost::asio::ip::tcp::socket &socket, std::string &machineId, std::string &path);

int promptChoice(BackupPB::AvailableWorkspaces);

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



bool restore(boost::asio::ip::tcp::socket &socket, std::string &machineId, std::string &path) {

    // Prepare restore message
    BackupPB::Workspace restore_request{};

    restore_request.set_machineid(machineId);
    restore_request.set_path(path);
    restore_request.set_restore(true);

    // Try to send request on socket
    // Returns if write fails
    try{
        writeToSocket<BackupPB::Workspace>(socket, restore_request);
    } catch(std::exception& e){
        std::cerr << "Socket write error: " << e.what() << std::endl;
        return false;
    }


    // Try to read the list of available workspaces from socket
    // Returns if read fails
    BackupPB::AvailableWorkspaces available_workspaces{};

    try{
        available_workspaces = readFromSocket<BackupPB::AvailableWorkspaces>(socket);
    } catch(std::exception& e) {
        std::cerr << "Socket read error: " << e.what() << std::endl;
        return false;
    }


    if(available_workspaces.status() == BackupPB::AvailableWorkspaces_Status_OK){
        int ind = promptChoice(available_workspaces);

        // Returning for non valid machine-path choice
        if(ind < 0){
            std::cerr << "The selected path to restore is not valid" << std::endl;
            return false;
        }

        // Selected folder to restore is located at index ind in paths
        BackupPB::MachinePath machine_path = available_workspaces.paths(ind);

        // Try to send MachinePath message to socket
        // Returns if write fails
        try{
            writeToSocket<BackupPB::MachinePath>(socket, machine_path);
        } catch(std::exception& e){
            std::cerr << "Socket write error: " << e.what() << std::endl;
            return false;
        }

        // Try to read a restore response from socket
        // Returns if read fails
        BackupPB::RestoreResponse restore_response{};

        try{
            restore_response = readFromSocket<BackupPB::RestoreResponse>(socket);
        } catch(std::exception& e) {
            std::cerr << "Socket read error: " << e.what() << std::endl;
            return false;
        }

        // Return if server rejected the request
        if(restore_response.status() == BackupPB::RestoreResponse_Status_FAIL){
            std::cerr << "Restore request has been rejected" << std::endl;
            return false;
        }

        // Read a JobRequest from the socket until a message with status END_RESTORE is received
        BackupPB::JobRequest job_request{};
        do{
            // Try to read JobRequest from socket
            // Returns if read fails
            try{
                job_request = readFromSocket<BackupPB::JobRequest>(socket);
            } catch(std::exception& e){
                std::cerr << "Socket read error: " << e.what() << std::endl;
                return false;
            }

            // Compute the correct path
            std::string complete_path{path + "/" + job_request.path()};

            // If the request is an ADD_FILE tries to read the file from the socket
            // Returns if read fails
            if(job_request.pbaction() == BackupPB::JobRequest_PBAction_ADD_FILE) {
                try {
                    receiveFile(socket, complete_path, job_request.size());
                } catch (std::exception &e) {
                    std::cerr << "Error while receiving file: " << e.what() << std::endl;
                    return false;
                }
            }

            // If the request is an ADD_DIRECTORY there is no socket read
            else if(job_request.pbaction() == BackupPB::JobRequest_PBAction_ADD_DIRECTORY)
                std::filesystem::create_directories(complete_path);

        } while(job_request.pbaction() != BackupPB::JobRequest_PBAction_END_RESTORE);

    }

    std::cout << "Restore completed" << std::endl;
    return true;
}

/**
 * Prompt and select the desired workspace
 * @param ws AvailableWorkspaces message
 * @return the index of the selected Workspace, -1 if error (empty message or index selected is out of bound)
 */
int promptChoice(BackupPB::AvailableWorkspaces ws){
    if(ws.paths().empty()) {
        std::cout<<"No workspace to restore available on the server"<<std::endl;
        return -1;
    }

    int i=1,choice;

    std::cout<<"Available workspaces to restore:"<<std::endl;
    for(BackupPB::MachinePath p : ws.paths()){
        std::cout<<i<<"- "<<p.path()<<" on "<<p.machineid()<<std::endl;
        i++;
    }
    std::cout<<"Enter the index:\n> ";
    std::cout.flush();
    std::cin>>choice;
    if(!std::cin){
        std::cout<<"Wrong input format"<<std::endl;
        return -1;
    }
    if(choice<1 || choice > ws.paths_size()) {
        std::cout<<"Index out of bound"<<std::endl;
        return -1;
    }

    return choice -1;
}

