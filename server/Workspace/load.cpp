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

/**
 * Function that loads the workspace requested by the user after login.
 *  If the user asks for a backup operation, the server checks that there are no other active sessions
 *      on the workspace and sends to the client every checksum in the current state of the selected workspace.
 *  If the user requests a restore operation, the server sends all the available workspaces to the client and waits for
 *      a response that will determine which workspace will be restored.
 *      If the user tries to restore a folder into a different, already existing and non-empty workspace, the operation
 *      fails; otherwise, an affermative reply is sent to the client.
 * @param socket to read/receive messages
 * @param username to compute the operations related to the server paths
 * @return a shared pointer to the path for the current session
 */
std::shared_ptr<PathPool> loadWorkspace(boost::asio::ip::tcp::socket& s, std::string& username){
    // Get IP address for log purposes
    std::string ipaddr = s.remote_endpoint().address().to_string();

    /* Read workspace from socket containing
        - client path
        - machineid
        - a flag which indicates if a restore or a backup operation has to be done
    */
    BackupPB::Workspace workspace;
    try{
        workspace = readFromSocket<BackupPB::Workspace>(s);
    }
    catch(std::exception& e){
        print_log_error(ipaddr,e.what());
        return nullptr;
    }

    // Restore flag is NOT active --> backup
    if(!workspace.restore()){
        print_log_message(ipaddr,username,"Backup request: " + workspace.path() + " @ " + workspace.machineid());
        std::string server_path;

        BackupPB::WorkspaceMetaInfo response{};
        response.set_status(BackupPB::WorkspaceMetaInfo_Status_OK);
        try{
            server_path = computeServerPath(username, workspace.machineid(), workspace.path());
            print_log_message(ipaddr,username, "Server path: " + workspace.path() + " -> " + server_path);
        }
        catch(std::exception& e){
            print_log_error(ipaddr,e.what());
            response.set_status(BackupPB::WorkspaceMetaInfo_Status_FAIL);

        }
        std::shared_ptr<PathPool> pool=nullptr;

        if(response.status()==BackupPB::WorkspaceMetaInfo_Status_OK)
            pool = std::make_shared<PathPool>(server_path, false);

        //If there is already another client that is using that workspace the session is terminated
        if(pool==nullptr|| !pool->isValid()){
            response.set_status(BackupPB::WorkspaceMetaInfo_Status_FAIL);
            try{
                writeToSocket(s, response);
            }
            catch(std::exception& e){
                print_log_error(ipaddr,e.what());
                return nullptr;
            }
            return pool;
        } else{

            // Retrieve folders, files and checksum and send to client
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
                        std::size_t size = directory_entry.file_size();
                        if(!checksum.has_value()){
                            response.set_status(BackupPB::WorkspaceMetaInfo_Status_FAIL);
                            response.clear_list();
                            break;
                        }
                        else{
                            message->set_checksum(checksum.value());
                            message->set_size(size);
                        }

                    }
                }
            }catch(std::exception& e){
                print_log_error(ipaddr, username, e.what());
                response.set_status(BackupPB::WorkspaceMetaInfo_Status_FAIL);
            }


            try{
                writeToSocket(s, response);
            }
            catch(std::exception& e){
                print_log_error(ipaddr, username, e.what());
                return nullptr;
            }
            if(response.status() == BackupPB::WorkspaceMetaInfo_Status_OK)
                return pool;
            else return nullptr;
        }
    }

    // Restore flag is active --> restore
    else{
        print_log_message(ipaddr,username,"Restore request");

        // Send available clientPath for that user
        std::set<std::pair<std::string, std::string>> availablePaths;
        BackupPB::AvailableWorkspaces availablePathMessage{};

        // Retrieve all the (machine,path) pairs the user has used for backup
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
            print_log_error(ipaddr,e.what());
            return nullptr;
        }
        if(availablePathMessage.status()==BackupPB::AvailableWorkspaces_Status_FAIL)
            return nullptr;

        // Receive chosen (machineID,path) pair
        BackupPB::MachinePath chosenPath;
        try{
            chosenPath = readFromSocket<BackupPB::MachinePath>(s);
        }
        catch(std::exception& e){
            print_log_error(ipaddr,e.what());
            return nullptr;
        }
        try{
            // If the selection of the folder to restore was not successful
            if(chosenPath.erroronselection())
                return nullptr;

            /* Check that, given a certain user, the chosen (machineID,path) combination of the folder to restore is ok
             * in particular, can not be accepted a combination where
             * - the (machineID,path) pair related to the folder where the user wants to copy the restored folder
             *   already exists on the server
             * - the (machineID,path) pair related to the folder that contains the content the user wants to restore,
             *   is different from the previous one.
             * This combination is not allowed since all the data contained in the first folder (on the server) would be lost
             */
            if( (chosenPath.machineid() != workspace.machineid()
                 || chosenPath.path() != workspace.path() )
                && isClientPathAlreadyPresent(username, workspace.machineid(), workspace.path())){
                BackupPB::RestoreResponse restoreResponse{};
                restoreResponse.set_status(BackupPB::RestoreResponse_Status_FAIL);
                writeToSocket(s, restoreResponse);
                return nullptr;
            }
        }
        catch(std::exception& e){
            print_log_error(ipaddr,e.what());
            return nullptr;
        }

        // Retrieve associated server path
        std::string server_path;
        try{
            server_path = computeServerPath(username, chosenPath.machineid(), chosenPath.path());
        } catch(std::exception& e){
            print_log_error(ipaddr, "Could not compute server path for user "+ username);
            print_log_error(ipaddr,e.what());
            return nullptr;
        }

        // Create PathPool, update db and send response to client (OK or FAIL)
        std::shared_ptr<PathPool> pool=std::make_shared<PathPool>(server_path, true);
        BackupPB::RestoreResponse restoreResponse{};

        try{
            if(!pool->isValid() || !updateMapping(username, chosenPath.machineid(), chosenPath.path(), workspace.machineid(), workspace.path()) )
                restoreResponse.set_status(BackupPB::RestoreResponse_Status_FAIL);
            else
                restoreResponse.set_status(BackupPB::RestoreResponse_Status_OK);
        } catch(std::exception& e){
            restoreResponse.set_status(BackupPB::RestoreResponse_Status_FAIL);
        }

        try{
            writeToSocket(s, restoreResponse);
        }
        catch(std::exception& e){
            return nullptr;
        }

        // If restore fails, set the response up with a failure message; otherwise server cache is updated
        if(pool->isValid()) {
            if(restoreResponse.status() == BackupPB::RestoreResponse_Status_FAIL)
                return nullptr;
            else
                cleanFileSystem(server_path);
        }
        return pool;
    }
}