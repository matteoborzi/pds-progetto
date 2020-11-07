//
// Created by rober on 06/10/2020.
//

#include <filesystem>
#include "dataManagement.h"
#include "../../common/messages/JobRequest.pb.h"
#include "../../common/job_utils.h"
#include "../Configuration/Configuration.h"
#include "../Configuration/file_util.h"
#include "../../common/messages/socket_utils.h"
#include "../../common/Checksum.h"
#include "../../common/messages/file_utils.h"
#include "../DirectoryStructure/File.h"
#include "../DirectoryStructure/utils.h"
#include "../../common/messages/JobResponse.pb.h"


void sendData(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket, JobQueue &queue) {
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
                std::cout<<"Sending "+j.getPath()<<" to the server\n";
                sendFile(socket, absolutePath, req.size());
            } catch (std::exception & e) {

                //TODO decide how handle errors
                std::cerr<<"Error while sending "+basePath+": "+e.what()+"\n";
                throw e;

            }

            //update checksum (if needed) in Directory structure
            std::shared_ptr<File> file = getFile(j.getPath());
            if (file != nullptr) {
                file->setChecksum(checksum);
            }
        }
    }

}

void receiveData(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket, JobQueue &queue) {
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
                counter++;
                queue.retry(response.path());
            }
            else throw std::runtime_error("Server is not working properly");
        }
        else{
            counter = 0;
            if(!response.has_checksum()) //status OK and it is an add_folder or a delete
                queue.setConcluded(response.path());
            else {
                std::cout<<response.path()+" sent correctly\n";

                //a file has been sent for an add_file or for an update
                std::shared_ptr<File> file = getFile(response.path());
                if(file == nullptr)
                    /*the file is not present anymore,
                    so nothing should be done and the job is removed from the sent queue */
                    queue.setConcluded(response.path());
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