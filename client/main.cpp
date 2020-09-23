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


#include "../common/Checksum.h"
#include "DirectoryStructure/utils.h"
#include "Configuration/file_util.h"
#include "../common/messages/file_utils.h"

bool login(boost::asio::ip::tcp::socket &, std::string &, std::string &);

bool chooseWorkspace(boost::asio::ip::tcp::socket &, std::string &, std::string &);

void sendData(boost::asio::ip::tcp::socket &, JobQueue &);

void receiveData(boost::asio::ip::tcp::socket &, JobQueue &);

bool restore(boost::asio::ip::tcp::socket &socket, std::string &machineId, std::string &path);

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

bool login(boost::asio::ip::tcp::socket &socket, std::string &username, std::string &password) {
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

bool chooseWorkspace(boost::asio::ip::tcp::socket &socket, std::string &machineId, std::string &path) {
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

void sendData(boost::asio::ip::tcp::socket &socket, JobQueue &queue) {
    while (true) {
        //get a job
        Job j = queue.getLastAndSetSent();

        BackupPB::JobRequest req;

        req.set_path(j.getPath());
        req.set_pbaction(toPBAction(j.getAct()));

        std::string basePath = Configuration::getConfiguration().value().getPath();
        std::string absolutePath = concatenatePath(basePath, j.getPath());

        bool fileToBeSent = false;

        //choose what to do
        //in case of add and update, check if file/folder still exists in file system
        if (j.getAct() == ADD_FILE || j.getAct() == UPDATE) {

            std::filesystem::directory_entry f{absolutePath};
            if (!f.exists()) {
                queue.setConcluded(j.getPath());
                break;
            }

            if (f.is_directory())
                throw std::runtime_error("Expected " + j.getPath() + " to be a file");

            req.set_size(f.file_size());

            fileToBeSent = true;
        }

        if (!writeToSocket(socket, req))
            throw std::runtime_error("Impossible to send <" + j.getPath() + ">'s job to the server");

        if (fileToBeSent) {
            //compute checksum (if needed)
            std::string checksum = computeChecksum(absolutePath);
            //send data
            try {
                sendFile(socket, absolutePath, req.size());
            } catch (std::exception &) {

                //TODO decide how handle errors

            }

            //update checksum (if needed) in Directory structure
            std::shared_ptr<File> file = getFile(j.getPath());
            if (file != nullptr) {
                file->setChecksum(checksum);
            }
        }
    }

}

void receiveData(boost::asio::ip::tcp::socket &socket, JobQueue &queue) {
    //TODO fare check che gli / sui path siano corretti
    static std::atomic_int counter = 0;
    while (true) {
        BackupPB::JobResponse response{};
        try{
            response = readFromSocket<BackupPB::JobResponse>(socket);
        }
        catch(std::exception& e){
            throw std::runtime_error("Error in receiving messages from server ");
        }

        if(response.status() == BackupPB::JobResponse_Status_FAIL){
            if(counter <= 10){
                queue.retry(response.path());
                counter++;
            }
            else throw std::runtime_error("Server is not working properly");
        }
        else{
            counter = 0;
            if(!response.has_checksum()) //status OK and it is an add_folder or a delete
                queue.setConcluded(response.path());
            else if(response.has_checksum()){ //a file has been sent for an add_file or for an update
                std::string basePath = Configuration::getConfiguration().value().getPath();
                std::shared_ptr<File> file = getFile(response.path());
                if(file == nullptr)
                    continue;
                else {
                    if(file->getChecksum() == response.checksum())
                        queue.setConcluded(response.path());
                    else
                        queue.retry(response.path());
                }
            }
        }
    }
}

bool restore(boost::asio::ip::tcp::socket &socket, std::string &machineId, std::string &path) {
    //send workspace choice

    //wait response

    //if available
        //prompt for choice
        //send to server

        //wait files and dir
    return true;
}

