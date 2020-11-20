//
// Created by rober on 06/10/2020.
//

#include <filesystem>
#include "jobManager.h"
#include "../../common/messages/socket_utils.h"
#include "../ChecksumStorage/ChecksumStorage.h"
#include "../../common/messages/JobResponse.pb.h"
#include "../../common/messages/file_utils.h"
#include "../log/log_utils.h"


void serveJobRequest(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket, std::string& serverPath, JobRequestQueue& queue){
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

void sendResponses(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket,  JobRequestQueue& queue, const std::string& base_path,
                   std::atomic_bool& stopped_other, std::atomic_bool& stopped_self, const std::string& user){
    // Get IP address for logs
    std::string ipaddr = socket.next_layer().remote_endpoint().address().to_string();

    while(!stopped_other && !stopped_self){
        BackupPB::JobRequest request = queue.dequeueJobRequest();
        if(!request.IsInitialized()){
            //got empty job to get awakened
            stopped_self=true;
        }else {
            BackupPB::JobResponse response{};
            response.set_path(request.path());

            std::string complete_path{base_path + request.path().substr(1, request.path().size())};
            switch (request.pbaction()) {
                case BackupPB::JobRequest_PBAction_ADD_FILE :
                case BackupPB::JobRequest_PBAction_UPDATE :
                    if (!updateChecksum(complete_path)) {
                        response.set_status(BackupPB::JobResponse_Status_FAIL);
                        print_log_error(ipaddr, user, "Error while storing "+complete_path);
                    } else {
                        std::optional<std::string> checksum = getChecksum(complete_path);
                        if (!checksum.has_value()) {
                            response.set_status(BackupPB::JobResponse_Status_FAIL);
                            print_log_error(ipaddr, user, "Error while computing checksum of "+complete_path);
                        }
                        else {
                            print_log_message(ipaddr, user, complete_path+" received correctly");
                            response.set_status(BackupPB::JobResponse_Status_OK);
                            response.set_checksum(checksum.value());
                        }
                    }
                    break;
                case BackupPB::JobRequest_PBAction_ADD_DIRECTORY:
                    print_log_message(ipaddr, user, complete_path+" created");
                    response.set_status(BackupPB::JobResponse_Status_OK);
                    break;
                case BackupPB::JobRequest_PBAction_DELETE :
                    if (!deleteFolderRecursively(complete_path)) {
                        print_log_message(ipaddr, user, "Error while deleting " +complete_path);
                        response.set_status(BackupPB::JobResponse_Status_FAIL);
                    }else {
                        response.set_status(BackupPB::JobResponse_Status_OK);
                        print_log_message(ipaddr, user, complete_path+" deleted");
                    }
                    break;
            }

            try {
                writeToSocket(socket, response);
            }
            catch (std::exception &e) {
                print_log_error(ipaddr, user, e.what());
                //stopping other thread
                stopped_self = true;
                return;
            }
        }
    }

    return;
}