//
// Created by rober on 06/10/2020.
//

#include <filesystem>
#include "restore.h"
#include "../../common/messages/Workspace.pb.h"
#include "../../common/messages/socket_utils.h"
#include "../../common/messages/AvailableWorkspaces.pb.h"
#include "../../common/messages/RestoreResponse.pb.h"
#include "../../common/messages/JobRequest.pb.h"
#include "../../common/messages/file_utils.h"

int promptChoice(BackupPB::AvailableWorkspaces);

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
                    std::cout<<job_request.path()<<" received"<<std::endl;
                } catch (std::exception &e) {
                    std::cerr << "Error while receiving "+job_request.path()+": " << e.what() << std::endl;
                    return false;
                }
            }

                // If the request is an ADD_DIRECTORY there is no socket read
            else if(job_request.pbaction() == BackupPB::JobRequest_PBAction_ADD_DIRECTORY)
                std::filesystem::create_directories(complete_path);

        } while(job_request.pbaction() != BackupPB::JobRequest_PBAction_END_RESTORE);

    }

    std::cout << "Restore completed successfully" << std::endl;
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