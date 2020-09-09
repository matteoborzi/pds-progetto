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

void watch(JobQueue &queue) {
    // getting configuration
    std::optional<Configuration> conf = Configuration::getConfiguration();
    if (!conf.has_value())
        throw std::runtime_error("Impossible to get configuration");
    //getting absolute path of folder to watch
    std::string abs_path = conf.value().getPath();
    bool first = true;

    while (true) {
        //clearing all previously visited elements
        Directory::getRoot()->unsetVisited();

        //scanning file system
        for (auto element : std::filesystem::recursive_directory_iterator{abs_path, std::filesystem::directory_options::skip_permission_denied}) {
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
                    queue.add(addFile);


                } else {

                    if ((! first && last_edit_time(element) > file->getLastEditTime() ) //file is newer than one in DirectoryStructure
                        //(only from second check)
                        || (first && file->getChecksum() != computeChecksum(element.path()))) { //different checksum
                        // (computing it only at first check)

                        //The file has been updated
                        Job update{path, UPDATE, true};
                        queue.add(update);

                        if(!first) //(otherwise this call is made in following lines)
                            //updating information about file
                            file->setLastEditTime(last_edit_time(element));


                    }
                    if(first)
                        //updating information about file (date not already present)
                        file->setLastEditTime(last_edit_time(element));

                }
                file->setVisited();
            }

        }

        //getting not visited entry to be deleted
        for (auto &entry : Directory::getRoot()->getNotVisited()) {
            std::string deletePath=entry.first;
            
            Job deleteDoF{entry.first, DELETE, entry.second->myType()==FILETYPE };
            queue.add(deleteDoF);

            deleteDirectoryOrFile(deletePath);
        }
        first = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
