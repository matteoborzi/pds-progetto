#include <iostream>
#include "initialization.h"

#include "../DirectoryStructure/utils.h"

#include "../../common/messages/AuthenticationRequest.pb.h"
#include "../../common/messages/AuthenticationResponse.pb.h"
#include "../../common/messages/socket_utils.h"
#include "../../common/messages/Workspace.pb.h"
#include "../../common/messages/MetaInfo.pb.h"

/**
 * this function implements the login functionality
 * @param socket to send/receive messages
 * @param username
 * @param password
 * @return true if login is successful
 */
bool login(boost::asio::ip::tcp::socket& socket, std::string &username, std::string &password) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    //send the credentials to the server
    BackupPB::AuthenticationRequest req;
    req.set_username(username);
    req.set_password(password);
    try {
        writeToSocket(socket, req);
    } catch (std::exception &e) {
        std::cerr << std::string(e.what()) + "\n";
        return false;
    }

    //waits for the response
    BackupPB::AuthenticationResponse response;
    try {
        response = readFromSocket<BackupPB::AuthenticationResponse>(socket);
    } catch (std::exception &e) {
        std::cerr << std::string(e.what()) + "\n";
        return false;
    }

    if (response.status() != BackupPB::AuthenticationResponse_Status_OK)
        return false;
    return true;
}

/**
 * this function performs the initial handshake where the client choose the workspace to work with;
 * then the server performs some checks, and if everything is ok, the client receives the metadata
 * of files contained on the server, and stores them in a Directory structure
 * @param socket to communicate with the server
 * @param machineId local identifier of the machine
 * @param path absolute path of the directory
 * @return true in case of success, false otherwise
 */
bool chooseWorkspace(boost::asio::ip::tcp::socket& socket, std::string &machineId, std::string &path) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    BackupPB::Workspace workspaceChoice;

    workspaceChoice.set_machineid(machineId);
    workspaceChoice.set_path(path);
    workspaceChoice.set_restore(false);

    try{
        writeToSocket(socket,workspaceChoice);
    } catch(std::exception& e){
        std::cerr << std::string(e.what()) + "\n";
        return false;
    }

    BackupPB::WorkspaceMetaInfo response;
    try{
        response = readFromSocket<BackupPB::WorkspaceMetaInfo>(socket);
    } catch(std::exception& e){
        std::cerr << std::string(e.what()) + "\n";
        return false;
    }

    if(response.status() != BackupPB::WorkspaceMetaInfo_Status_OK){
        return false;
    }

    //for each element of the list, add it to the structure
    for(BackupPB::DirectoryEntryMessage directoryEntry : response.list()){
        switch (directoryEntry.type()) {

            case BackupPB::DirectoryEntryMessage_Type_DIRTYPE:
                if(!addDirectory(directoryEntry.name()))
                    return false;
                break;

            case BackupPB::DirectoryEntryMessage_Type_FILETYPE:
                if(!directoryEntry.has_checksum())
                    return false;
                std::string filePath{directoryEntry.name()};
                std::string checksum{directoryEntry.checksum()};
                std::size_t size{directoryEntry.size()};
                if(!addFile(filePath, checksum, 0, size))
                    return false;
                break;
        }
    }

    return true;
}
