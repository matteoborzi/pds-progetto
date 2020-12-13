#include <filesystem>
#include "dataManagement.h"

#include "../Configuration/Configuration.h"
#include "../Configuration/file_util.h"
#include "../DirectoryStructure/File.h"
#include "../DirectoryStructure/utils.h"

#include "../../common/Checksum.h"
#include "../../common/job_utils.h"

#include "../../common/messages/socket_utils.h"
#include "../../common/messages/file_utils.h"
#include "../../common/messages/JobResponse.pb.h"

#define MAX_RETRY 10

/**
 * this function is executed by the thread whose goal is
 * to take one Job at a time from the JobQueue and send it to the server
 * (eventually sending also the file to add/update)
 * @param socket to send messages/data
 * @param queue to get the Job
 * @param termination atomic_bool passed by reference to understand whether it has to terminate or not
 */
void sendData(boost::asio::ip::tcp::socket& socket, JobQueue &queue, std::atomic_bool &termination) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    while (!termination) {
        //get a job from the queue
        Job j = queue.getLastAndSetSent();
        //check if the job is the one inserted to notify the thread for termination
        if (j.isTermination()){
            return;
        }
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
                //if it does not exists anymore, remove the job from the sent queue
                queue.setConcluded(j.getPath());
                continue;
            }

            if (f.is_directory()) {
                std::cerr << "Expected " + j.getPath() + " to be a file\n";
                termination = true;
                continue;
            }

            req.set_size(f.file_size());

            fileToBeSent = true;
        } else if(j.getAct() == ADD_DIRECTORY){
            std::string message = "Adding folder " + j.getPath() + "\n";
            std::cout << message;
        } else if(j.getAct() == DELETE){
            std::string message = "Deleting " + j.getPath() + "\n";
            std::cout << message;
        }
        try {
            writeToSocket(socket, req);
            if (fileToBeSent) {
                //compute checksum (if a file has to be sent)
                std::string checksum = computeChecksum(absolutePath);
                //send data
                std::string message = "Sending " + j.getPath() + " to the server\n";
                std::cout << message;
                sendFile(socket, absolutePath, req.size());

                //update checksum (if a file has been sent) in Directory structure
                std::shared_ptr<File> file = getFile(j.getPath());
                if (file != nullptr) {
                    file->setChecksum(checksum);
                }
            }
        } catch (std::exception &e) {
            std::cerr << "Error while sending " + j.getPath() + ": " + e.what() + "\n";
            termination= true;
            continue;
        }
    }
    //the functions executes this lines in case of termination
    //it wakes the other threads eventually waiting on the queue and close the socket

    close_socket(socket);
    queue.wakeAll();

    return;
}

/**
 * this function is executed by the thread whose goal is
 * to receive responses from the server about the previously sent Jobs
 * and, basing on the response, either set the Job as concluded and remove it from the sent queue
 * or retry the Job putting it again in the queue of Jobs to be sent
 * @param socket to receive messages
 * @param queue to remove/put Jobs
 * @param termination atomic_bool passed by reference to understand whether it has to terminate or not
 */
void receiveData(boost::asio::ip::tcp::socket& socket, JobQueue &queue, std::atomic_bool &termination) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    static std::atomic_int counter = 0;
    while (!termination) {
        BackupPB::JobResponse response{};
        try {
            //get a response from the server
            response = readFromSocket<BackupPB::JobResponse>(socket);
        }
        catch (std::exception &e) {
            std::string message = "Error in listening from the socket: " + std::string(e.what()) +"\n";
            std::cerr << message;
            termination= true;
            continue;
        }

        //the Job's execution failed for some reason
        if (response.status() == BackupPB::JobResponse_Status_FAIL) {
            //the counter is used to count the number of consecutive fails
            //once reached the MAX_RETRY number, probably there is a problem on the server
            // so the thread terminates
            if (counter <= MAX_RETRY) {
                counter++;
                queue.retry(response.path());
            } else {
                std::cerr<<"Server is not working properly\n";
                termination = true;
                continue;
            }
        } else {
            //set to 0 again if the Job didn't fail
            counter = 0;
            if (!response.has_checksum()) //status OK and it is an add_folder or a delete
                queue.setConcluded(response.path());
            else {
                std::string message = "------> " + response.path() + " sent correctly\n";
                std::cout << message;
                //a file has been sent for an add_file or for an update
                std::shared_ptr<File> file = getFile(response.path());
                if (file == nullptr)
                    /* the file is not present anymore,
                    so nothing should be done and the job is removed from the sent queue */
                    queue.setConcluded(response.path());
                else {
                    // check if the checksum of the file sent to the server
                    // and of the one received by the server are equal
                    if (file->getChecksum() == response.checksum())
                        queue.setConcluded(response.path());
                    else
                        queue.retry(response.path());
                }
            }
        }
    }

    //the functions executes this lines in case of termination
    //it wakes the other threads eventually waiting on the queue and close the socket
    close_socket(socket);
    queue.wakeAll();

    return;
}