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

void watch(JobQueue& queue){
    std::optional<Configuration> conf=Configuration::getConfiguration();
    if(!conf.has_value())
        throw std::runtime_error("Impossible to get configuration");
    std::string abs_path = conf.value().getPath();
    bool first=true;
    //TODO change first to true
    while(first){
        int count=0;
        for(auto element : std::filesystem::recursive_directory_iterator{abs_path}){
            std::string path=element.path();
            path= path.substr(abs_path.size(),path.size());
            std::cout<<path<<std::endl;
            if(element.is_directory()){
                std::shared_ptr<Directory> dir = getDirectory(path);
                if(dir== nullptr){
                    addDirectory(path);
                    dir=getDirectory(path);
                    if(dir== nullptr) {
                        throw std::runtime_error("Unable to create metadata for dir "+path);
                    }
                    Job addDir{path,ADD_DIRECTORY, false};
                    queue.add(addDir);
                }

                dir->setVisited();


            }else{

            }
        }

        first=false;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
