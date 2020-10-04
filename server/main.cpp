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

std::optional<std::string> doAuthentication(boost::asio::ip::tcp::socket& );
std::shared_ptr<PathPool> loadWorkspace(boost::asio::ip::tcp::socket&, std::string&);
void serveJobRequest(boost::asio::ip::tcp::socket&, std::string&, JobRequestQueue&);
void sendResponses(boost::asio::ip::tcp::socket&,  JobRequestQueue&, const std::string&);
void cleanFileSystem(const std::string& );
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

std::optional<std::string> doAuthentication(boost::asio::ip::tcp::socket& s){

    BackupPB::AuthenticationRequest authenticationRequest;
    BackupPB::AuthenticationResponse authenticationResponse;
    std::optional<std::string> username;

    try{
        authenticationRequest = readFromSocket<BackupPB::AuthenticationRequest>(s);
    } catch(std::exception& e) {
        std::cerr<< e.what() << std::endl;
        return std::nullopt;
    }

    if(!authenticate(authenticationRequest.username(), authenticationRequest.password())){
        //std::cerr << "Login failed" << std::endl;
        authenticationResponse.set_status(BackupPB::AuthenticationResponse_Status_FAIL);
        username = std::nullopt;
    } else {
        authenticationResponse.set_status(BackupPB::AuthenticationResponse_Status_OK);
        username = authenticationRequest.username();
    }

    try{
        writeToSocket(s, authenticationResponse);
    } catch(std::exception& e){
        std::cerr << e.what() << std::endl;
        return std::nullopt;
    }

    return username;
}

std::shared_ptr<PathPool> loadWorkspace(boost::asio::ip::tcp::socket& s, std::string& username){

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
        PathPool pool{server_path, true};
        BackupPB::RestoreResponse restoreResponse{};

        try{
            if(!pool.isValid() || !updateMapping(username, chosenPath.machineid(), chosenPath.path(), workspace.machineid(), workspace.path()) )
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

        if(pool.isValid()) {
            if(restoreResponse.status() == BackupPB::RestoreResponse_Status_FAIL)
                return nullptr;
            else
                cleanFileSystem(server_path);
        }
        return std::make_shared<PathPool>(pool);
    }
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
                sendFile(socket, path, request.size());
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

void cleanFileSystem(const std::string& path){
    std::filesystem::directory_entry dir{path};
    if(!dir.exists() || !dir.is_directory())
        throw std::logic_error("Expecting an existing folder but get "+path);
    for(std::filesystem::directory_entry element : std::filesystem::recursive_directory_iterator(path)) {
        //scan recursively all files in path
        std::string file_path{element.path().string()};
        if(element.is_regular_file() && boost::algorithm::ends_with(element.path().string(), TMP_EXTENSION)) {
            boost::algorithm::erase_last(file_path, std::string{TMP_EXTENSION});

            std::filesystem::directory_entry old{file_path};
            // if (.tmp is present && normal !present)
            if(!old.exists())
                updateChecksum(file_path);
            else
                // if (both presents)
                //keep older
                std::filesystem::remove(file_path+TMP_EXTENSION);
        }
    }
}