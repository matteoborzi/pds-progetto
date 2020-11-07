//
// Created by rober on 06/10/2020.
//

#include <iostream>
#include "initialization.h"
#include "../../common/messages/AuthenticationRequest.pb.h"
#include "../../common/messages/AuthenticationResponse.pb.h"
#include "../../common/messages/socket_utils.h"
#include "../../common/messages/Workspace.pb.h"
#include "../../common/messages/MetaInfo.pb.h"
#include "../DirectoryStructure/utils.h"


bool login(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket, std::string &username, std::string &password) {
    BackupPB::AuthenticationRequest req;

    req.set_username(username);
    req.set_password(password);

    try {
        writeToSocket(socket, req);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    BackupPB::AuthenticationResponse response;
    try {
        response = readFromSocket<BackupPB::AuthenticationResponse>(socket);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    if (response.status() != BackupPB::AuthenticationResponse_Status_OK)
        return false;
    return true;
}

bool chooseWorkspace(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket, std::string &machineId, std::string &path) {
    BackupPB::Workspace workspaceChoice;

    workspaceChoice.set_machineid(machineId);
    workspaceChoice.set_path(path);
    workspaceChoice.set_restore(false);

    try{
        writeToSocket(socket,workspaceChoice);
    } catch(std::exception& e){
        std::cerr << e.what() << std::endl;
        return false;
    }

    BackupPB::WorkspaceMetaInfo response;
    try{
        response = readFromSocket<BackupPB::WorkspaceMetaInfo>(socket);
    } catch(std::exception& e){
        std::cerr << e.what() << std::endl;
        return false;
    }

    if(response.status() != BackupPB::WorkspaceMetaInfo_Status_OK){
        return false;
    }

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
                if(!addFile(filePath, checksum, 0))
                    return false;
                break;
        }
    }

    return true;
}
