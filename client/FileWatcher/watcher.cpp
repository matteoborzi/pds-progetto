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
    std::optional<Configuration> conf = Configuration::getConfiguration();
    if (!conf.has_value())
        throw std::runtime_error("Impossible to get configuration");
    std::string abs_path = conf.value().getPath();
    bool first = true;

    while (true) {
        //TODO clear flags
        for (auto element : std::filesystem::recursive_directory_iterator{abs_path}) {
            std::string path = element.path();
            if (abs_path != "/")
                path = path.substr(abs_path.size(), path.size());
            if (element.is_directory()) {
                std::shared_ptr<Directory> dir = getDirectory(path);
                if (dir == nullptr) {
                    addDirectory(path);
                    dir = getDirectory(path);
                    if (dir == nullptr) {
                        throw std::runtime_error("Unable to create metadata for dir " + path);
                    }
                    Job addDir{path, ADD_DIRECTORY, false};
                    queue.add(addDir);
                }

                dir->setVisited();


            } else {
                std::shared_ptr<File> file = getFile(path);
                if (file == nullptr) {
                    addFile(path);
                    file = getFile(path);
                    if (file == nullptr) {
                        throw std::runtime_error("Unable to create metadata for file " + path);
                    }
                    Job addFile{path, ADD_FILE, true};
                    queue.add(addFile);

                    file->setVisited();
                } else {

                    if (last_edit_time(element) > file->getLastEditTime() //file is newer than the server one
                        // (if first time, otherwise a simple update of the file)
                        || (first && file->getChecksum() != computeChecksum(element.path()))) { //different checksum
                        Job update{path, UPDATE, true};
                        queue.add(update);

                        file->setVisited();
                    }

                }
            }
            for (auto &entry : Directory::getRoot()->getNotVisited()) {
                // TODO fix path (only name now)
                // entry->setVisited(false);
                // deleteDirectoryOrFile(entry->getName());
                Job deleteDoF{entry->getName(), DELETE, entry->myType()==FILETYPE };
                queue.add(deleteDoF);
            }
        }

        first = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
