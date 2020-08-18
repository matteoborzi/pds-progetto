//
// Created by rober on 18/08/2020.
//

#include <string>
#include <filesystem>
#include "filesystem.h"


void deleteFolder(std::string folder){
    std::filesystem::remove_all("./"+folder);

}

void createFolderIfNotExist(std::string folder) {
    std::filesystem::directory_entry dir{"./"+folder};

    if(!dir.exists())
        std::filesystem::create_directory(folder);
}
