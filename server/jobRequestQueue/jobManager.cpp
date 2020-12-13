#include <filesystem>
#include "jobManager.h"
#include "../../common/messages/socket_utils.h"
#include "../ChecksumStorage/ChecksumStorage.h"
#include "../../common/messages/JobResponse.pb.h"
#include "../../common/messages/file_utils.h"
#include "../log/log_utils.h"

/**
 * Function that reads a JobRequest from the socket.
 *      If a file is created or updated, the file is read from the socket and stored
 *          in the local filesystem with a temporary extension.
 *      If a directory is created, it creates the corresponding directory.
 *      Deletion actions are not performed here.
 * At last, the job is inerted into a queue in order to send a response to the client.
 * Exception thrown by read/write operations on socket are not handled here.
 * @param socket
 * @param serverPath
 * @param queue
 */
void serveJobRequest(boost::asio::ip::tcp::socket& socket, std::string& serverPath, JobRequestQueue& queue){
    // Get job request
    BackupPB::JobRequest req = readFromSocket<BackupPB::JobRequest>(socket);
    // Removing initial /
    std::string path{serverPath+req.path().substr(1,req.path().size() )};

    if(req.pbaction()==BackupPB::JobRequest_PBAction_ADD_FILE ||req.pbaction()==BackupPB::JobRequest_PBAction_UPDATE )
        // Add_file && update -> receive file, save into temporary and put into queue
        receiveFile(socket, path+TMP_EXTENSION, req.size());
    else if(req.pbaction()==BackupPB::JobRequest_PBAction_ADD_DIRECTORY)
        std::filesystem::create_directories(path);

    // Saving in queue
    queue.enqueueJobRequest(req);

}

/**
 * This function extracts an element from the internal server JobRequest queue and
 * performs the corresponding action on the checksum DB storage, then sends a response
 * with the status (and eventually the new checksum) to the client on the socket.
 * @param socket
 * @param queue
 * @param base_path
 * @param stopped_other
 * @param stopped_self
 * @param user
 */
void sendResponses(boost::asio::ip::tcp::socket& socket,  JobRequestQueue& queue, const std::string& base_path,
                   std::atomic_bool& stopped_other, std::atomic_bool& stopped_self, const std::string& user){
    // Get IP address for logs
    std::string ipaddr = socket.remote_endpoint().address().to_string();

    while(!stopped_other && !stopped_self){
        BackupPB::JobRequest request = queue.dequeueJobRequest();
        if(!request.IsInitialized()){
            // Got empty job to get awakened
            stopped_self=true;
        }else {
            // Response is set up
            BackupPB::JobResponse response{};
            response.set_path(request.path());

            // Compute the complete server path
            std::string complete_path{base_path + request.path().substr(1, request.path().size())};

            switch (request.pbaction()) {
                // If a file is created or updated, checksum is computed and stored
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
                //If a file or a directory is deleted its mapping is removed
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

            // Write on the socket
            try {
                writeToSocket(socket, response);
            }
            catch (std::exception &e) {
                print_log_error(ipaddr, user, e.what());
                // Stopping other thread
                stopped_self = true;
                return;
            }
        }
    }

    return;
}