//
// Created by rober on 06/10/2020.
//

#include "load.h"
#include <iostream>
#include <filesystem>
#include <boost/algorithm/string.hpp>
#include "./workspace_utils.h"
#include "../log/log_utils.h"
#include "../../common/messages/Workspace.pb.h"
#include "../../common/messages/socket_utils.h"
#include "../../common/messages/MetaInfo.pb.h"
#include "../../common/messages/AvailableWorkspaces.pb.h"
#include "../../common/messages/MachinePath.pb.h"
#include "../ChecksumStorage/ChecksumStorage.h"
#include "../../common/messages/RestoreResponse.pb.h"


std::shared_ptr<PathPool> loadWorkspace(boost::asio::ip::tcp::socket& s, std::string& username){
    // Get IP address for log purposes
    std::string ipaddr = s.remote_endpoint().address().to_string();

    /*read workspace from socket containing
        -client path
        -machineid
        -a flag which indicates if a restore or a backup operation has to be done
    */
    BackupPB::Workspace workspace;
    try{
        workspace = readFromSocket<BackupPB::Workspace>(s);
    }
    catch(std::exception& e){
        std::cerr << e.what() << std::endl;
        return nullptr;
    }

    if(!workspace.restore()){

        //restore flag is NOT active --> backup
        print_log_message(ipaddr,username,"Backup request");
        std::string server_path;

        BackupPB::WorkspaceMetaInfo response{};
        response.set_status(BackupPB::WorkspaceMetaInfo_Status_OK);
        try{
            server_path = computeServerPath(username, workspace.machineid(), workspace.path());
        }
        catch(std::exception& e){
            std::cerr << e.what() << std::endl;
            response.set_status(BackupPB::WorkspaceMetaInfo_Status_FAIL);

        }
        std::shared_ptr<PathPool> pool=nullptr;

        if(response.status()==BackupPB::WorkspaceMetaInfo_Status_OK)
            pool = std::make_shared<PathPool>(server_path, false);

        if(pool==nullptr|| !pool->isValid()){ //there is already another client that is using that workspace
            response.set_status(BackupPB::WorkspaceMetaInfo_Status_FAIL);
            try{
                writeToSocket(s, response);
            }
            catch(std::exception& e){
                std::cerr << e.what() << std::endl;
                return nullptr;
            }
            return pool;
        } else{

            //retrieve folders, files and checksum and send to client

            try {
                cleanFileSystem(server_path);
                for(auto directory_entry : std::filesystem::recursive_directory_iterator(server_path)){
                    BackupPB::DirectoryEntryMessage* message = response.add_list();
                    std::string name = directory_entry.path();
                    boost::algorithm::erase_first(name, server_path);
                    message->set_name("/"+name);
                    if(directory_entry.is_directory())
                        message->set_type(BackupPB::DirectoryEntryMessage_Type_DIRTYPE);
                    else {
                        message->set_type(BackupPB::DirectoryEntryMessage_Type_FILETYPE);
                        std::optional<std::string> checksum = getChecksum(directory_entry.path());
                        if(!checksum.has_value()){
                            response.set_status(BackupPB::WorkspaceMetaInfo_Status_FAIL);
                            response.clear_list();
                            break;
                        }
                        else
                            message->set_checksum(checksum.value());

                    }
                }
            }catch(std::exception& e){
                std::cerr << e.what() << std::endl;
                response.set_status(BackupPB::WorkspaceMetaInfo_Status_FAIL);
            }


            try{
                writeToSocket(s, response);
            }
            catch(std::exception& e){
                std::cerr << e.what() << std::endl;
                return nullptr;
            }
            if(response.status() == BackupPB::WorkspaceMetaInfo_Status_OK)
                return pool;
            else return nullptr;
        }
    }
    else{
        //restore flag is active --> restore
        print_log_message(ipaddr,username,"Restore request");
        //send available clientPath for that user
        std::set<std::pair<std::string, std::string>> availablePaths;
        BackupPB::AvailableWorkspaces availablePathMessage{};

        try{
            availablePaths = getAvailableClientPath(username);

            for(std::pair<std::string,std::string> entry : availablePaths){
                BackupPB::MachinePath* machinePath = availablePathMessage.add_paths();
                machinePath->set_path(entry.second);
                machinePath->set_machineid(entry.first);
            }
            availablePathMessage.set_status(BackupPB::AvailableWorkspaces_Status_OK);
        } catch (...) {
            availablePathMessage.set_status(BackupPB::AvailableWorkspaces_Status_FAIL);
            availablePathMessage.clear_paths();
        }


        try{
            writeToSocket(s, availablePathMessage);
        }
        catch(std::exception& e){
            std::cerr << e.what() << std::endl;
            return nullptr;
        }
        if(availablePathMessage.status()==BackupPB::AvailableWorkspaces_Status_FAIL)
            return nullptr;

        //receive chosen machineID,path
        BackupPB::MachinePath chosenPath;
        try{
            chosenPath = readFromSocket<BackupPB::MachinePath>(s);
        }
        catch(std::exception& e){
            std::cerr << e.what() << std::endl;
            return nullptr;
        }
        try{
            // if the selection of the folder to restore was not successful
            if(chosenPath.erroronselection())
                return nullptr;

            /* check that, given a certain user, the chosen combination machineID-path of the folder to restore is ok
             * in particular, can not be accepted a combination where
             * - the machineID-path related to the folder where the user wants to copy the restored folder
             *   already exists on the server
             * - the machineID-path related to the folder whose content the user wants to restore,
             *   is different with respect to the previous one.
             * this combination is not allowed since all the data contained in the first folder (on the server) would be loss
             */
            if( (chosenPath.machineid() != workspace.machineid()
                 || chosenPath.path() != workspace.path() )
                && isClientPathAlreadyPresent(username, workspace.machineid(), workspace.path())){
                std::cerr << "Error, the mapping "+username+", "+workspace.machineid()+", "+workspace.path()+" already exists"+
                             " and can not be overwritten " << std::endl;
                BackupPB::RestoreResponse restoreResponse{};
                restoreResponse.set_status(BackupPB::RestoreResponse_Status_FAIL);
                writeToSocket(s, restoreResponse);
                return nullptr;
            }
        }
        catch(std::exception& e){
            std::cerr << e.what() << std::endl;
            return nullptr;
        }

        //retrieve associated server path
        std::string server_path;
        try{
            server_path = computeServerPath(username, chosenPath.machineid(), chosenPath.path());
        } catch(std::exception& e){
            std::cerr << "Could not compute server path for user " << username << std::endl;
            std::cerr << e.what() << std::endl;
            return nullptr;
        }

        //create PathPool, update db and send response to client (OK or FAIL)
        std::shared_ptr<PathPool> pool=std::make_shared<PathPool>(server_path, true);
        BackupPB::RestoreResponse restoreResponse{};

        try{
            if(!pool->isValid() || !updateMapping(username, chosenPath.machineid(), chosenPath.path(), workspace.machineid(), workspace.path()) )
                restoreResponse.set_status(BackupPB::RestoreResponse_Status_FAIL);
            else
                restoreResponse.set_status(BackupPB::RestoreResponse_Status_OK);
        } catch(std::exception& e){
            std::cerr << "Could not update DB mapping for user " << username << std::endl;
            std::cerr << e.what() << std::endl;
            restoreResponse.set_status(BackupPB::RestoreResponse_Status_FAIL);
        }

        try{
            writeToSocket(s, restoreResponse);
        }
        catch(std::exception& e){
            std::cerr << e.what() << std::endl;
            return nullptr;
        }

        if(pool->isValid()) {
            if(restoreResponse.status() == BackupPB::RestoreResponse_Status_FAIL)
                return nullptr;
            else
                cleanFileSystem(server_path);
        }
        return pool;
    }
}