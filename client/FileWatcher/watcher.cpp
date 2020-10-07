//
// Created by rober on 11/08/2020.
//

#include <optional>
#include <thread>
#include <filesystem>
#include "watcher.h"
#include "../Configuration/Configuration.h"
#include "../DirectoryStructure/Directory.h"
#include "../DirectoryStructure/utils.h"
#include "../../common/Checksum.h"

#define MAX_RETRY 5

void watch(JobQueue &queue) {
    // getting configuration
    std::optional<Configuration> conf = Configuration::getConfiguration();
    if (!conf.has_value())
        throw std::runtime_error("Impossible to get configuration");
    //getting absolute path of folder to watch
    std::string abs_path = conf.value().getPath();
    bool first = true;

    int error_count=0;

    while (true) {
        
        //clearing all previously visited elements
       unsetAllVisited();

        //scanning file system
        std::filesystem::recursive_directory_iterator iter={abs_path, std::filesystem::directory_options::skip_permission_denied};

        bool error=false;

        while(iter!=end(iter)) {
            std::filesystem::directory_entry element= *iter;

            std::string path = element.path();
            if (abs_path != "/")
                //extracting relative path
                path = path.substr(abs_path.size(), path.size());

            if (element.is_directory()) {
                //looking for a directory in DirectoryStructure
                std::shared_ptr<Directory> dir = getDirectory(path);
                if (dir == nullptr) {
                    //directory must be added
                    addDirectory(path);
                    dir = getDirectory(path);
                    if (dir == nullptr) {
                        throw std::runtime_error("Unable to create metadata for dir " + path);
                    }
                    Job addDir{path, ADD_DIRECTORY, false};
                    queue.add(addDir);
                    std::cout<<"ADDING DIR: "<<path<<std::endl;
                }
                //otherwise nothing to do (a directory cannot be updated)
                dir->setVisited();


            } else if(element.is_regular_file()){
                //looking for a file
                std::shared_ptr<File> file = getFile(path);
                if (file == nullptr) {
                    //file not existing
                    addFile(path);
                    file = getFile(path);
                    if (file == nullptr) {
                        throw std::runtime_error("Unable to create metadata for file " + path);
                    }
                    Job addFile{path, ADD_FILE, true};
                    std::cout<<"ADDING FILE: "<<path<<std::endl;
                    queue.add(addFile);


                } else {
                    time_t edit_time;
                    std::string checksum;
                    try {
                        edit_time = last_edit_time(element);
                        if (first)
                            checksum = computeChecksum(element.path());
                    }catch(std::exception& e){
                        //TODO remove print
                        std::cout<<"Winzoz fa schifo: "<<e.what()<<std::endl;
                        //TODO fare meglio sta roba
                        try{
                            iter++;
                        }catch(std::exception& e){
                            //TODO remove print
                            std::cout<<"Winzoz fa schifo pt2"<<e.what()<<std::endl;
                            error=true;
                            break;
                        }

                        continue;
                    }


                    if ((! first &&  edit_time> file->getLastEditTime() ) //file is newer than one in DirectoryStructure
                        //(only from second check)
                        || (first && file->getChecksum() != checksum)) { //different checksum
                        // (computing it only at first check)

                        //The file has been updated
                        Job update{path, UPDATE, true};
                        queue.add(update);

                        if(!first) //(otherwise this call is made in following lines)
                            //updating information about file
                            file->setLastEditTime(edit_time);


                    }
                    if(first)
                        //updating information about file (date not already present)
                        file->setLastEditTime(last_edit_time(element));

                }
                file->setVisited();
            }
            try{
                iter++;
            }catch(std::exception& e){
                //TODO remove print
                std::cout<<"Winzoz fa schifo pt2"<<e.what()<<std::endl;
                error=true;
                break;
            }
        }

        if(error) {
            error_count++;
            if(error_count>=MAX_RETRY)
                //TODO decide if exception is needed
                return;
            continue;
        }

        error_count=0;

        //getting not visited entry to be deleted
        for (auto &entry : getNotVisited()) {
            std::cout << "Deleting " + entry.first<< std::endl;
            std::string deletePath=entry.first;
            
            Job deleteDoF{deletePath, DELETE, entry.second->myType()==FILETYPE };
            queue.add(deleteDoF);

            deleteDirectoryOrFile(deletePath);
        }
        first = false;

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}
