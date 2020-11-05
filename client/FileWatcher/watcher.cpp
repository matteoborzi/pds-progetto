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
#define WATCH_PERIOD 5

bool tryIncrement(std::filesystem::recursive_directory_iterator &iterator);

/**
 * Periodically checks the fileSystem to detect changes w.r.t the Directory structure
 * @param queue where to insert jobs
 * @param termination flag that will be set on conclusion ore determine the end of the function
 */
void watch(JobQueue &queue, std::atomic_bool& termination) {
    // getting configuration
    std::optional<Configuration> conf = Configuration::getConfiguration();
    if (!conf.has_value())
        throw std::runtime_error("Impossible to get configuration");
    //getting absolute path of folder to watch
    std::string abs_path = conf.value().getPath();
    bool first = true;

    int error_count=0;

    while (!termination) {
        
        //clearing all previously visited elements
       unsetAllVisited();

        //scanning file system avoiding files with permission denied
        std::filesystem::recursive_directory_iterator iter={abs_path, std::filesystem::directory_options::skip_permission_denied};

        bool error=false;

        while(iter!=end(iter)) {
            //getting current element of the iterator
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

                    //creating the job to perform
                    Job addDir{path, ADD_DIRECTORY, false};
                    queue.add(addDir);
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
                        //TODO manage case of delete folder + create file (and viceversa) with same name
                        throw std::runtime_error("Unable to create metadata for file " + path);
                    }

                    //creating the job to perform
                    Job fileToAdd{path, ADD_FILE, true};
                    queue.add(fileToAdd);


                } else {
                    time_t edit_time;
                    std::string checksum;
                    std::size_t size;
                    try {

                        //computing infos of the file
                        edit_time = last_edit_time(element);
                        size = element.file_size();
                        if (first && size == file->getSize())
                            //checksum is computed only at first iteration
                            //  and if size on client differs from the server one
                            // (in other iterations date and size are considered sufficient to detect changes)
                            checksum = computeChecksum(element.path());
                    }catch(std::exception& e){
                        //file does not exist anymore
                        if(!tryIncrement(iter)){
                            error= true;
                            break;
                        }

                        continue;
                    }


                    if ((! first &&  (edit_time> file->getLastEditTime() || size != file->getSize()))
                        //file is newer/different than the one in DirectoryStructure
                        //(only from second check)
                        || (first && (file->getSize() != size || file->getChecksum() != checksum))) { //different checksum
                        // (computing it only at first check)

                        //The file has been updated
                        Job update{path, UPDATE, true};
                        queue.add(update);

                        if(!first) { //(otherwise this call is made in following lines)
                            //updating information about file
                            file->setLastEditTime(edit_time);
                            file->setSize(size);
                        }


                    }
                    if(first) {
                        //updating information about file (date is not already present)
                        file->setLastEditTime(last_edit_time(element));
                        file->setSize(size);
                    }

                }
                file->setVisited();
            }
            if(!tryIncrement(iter)){
                error= true;
                break;
            }
        }

        if(error) {
            //error while trying to increment the directory iterator
            error_count++;
            if(error_count>=MAX_RETRY)
                throw std::runtime_error("Maximum number of consecutive folder scan error exceeded");
            //retry to scan the whole folder
            continue;
        }

        //no error detected in last scan
        error_count=0;

        //getting not visited entry to be deleted
        for (auto &entry : getNotVisited()) {
            std::string deletePath=entry.first;
            
            Job deleteDoF{deletePath, DELETE, entry.second->myType()==FILETYPE };
            queue.add(deleteDoF);

            deleteDirectoryOrFile(deletePath);
        }
        first = false;

        std::this_thread::sleep_for(std::chrono::seconds(WATCH_PERIOD));
    }
}

/**
 * The function tries to increment the scan of the given directory_iterator
 * @param iterator
 * @return true on success
 */
bool tryIncrement(std::filesystem::recursive_directory_iterator &iterator) {
    try{
        iterator++;
    } catch (...) {
        return false;
    }
    return true;
}
