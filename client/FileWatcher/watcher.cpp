//
// Created by rober on 11/08/2020.
//

#include <optional>
#include <thread>
#include <filesystem>
#include "watcher.h"
#include "../Configuration/Configuration.h"

void watch(JobQueue& queue){
    std::optional<Configuration> conf=Configuration::getConfiguration();
    if(!conf.has_value())
        throw std::runtime_error("Impossible to get configuration");
    std::string abs_path = conf.value().getPath();
    while(true){
        for(auto element : std::filesystem::recursive_directory_iterator{abs_path}){
            std::cout<<element<<std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
