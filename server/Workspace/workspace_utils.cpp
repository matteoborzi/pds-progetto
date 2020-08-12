//
// Created by Angelica on 12/08/2020.
//

#include <filesystem>
#include "workspace_utils.h"
#define filename "mapping.csv"

/**
 * this function should be called to retrieve,
 * basing on
 * @param username
 * @param machineID
 * @param client absolute path of the folder,
 * the server path where the user's folder is copied
 */
std::string computeServerPath(std::string user, std::string machineID, std::string client_path){
    /*
     * when this function is called,
     * normally the path ./user/machineID should exists
     */
    std::filesystem::directory_entry machine_folder{"./"+user+"/"+machineID};
    if(!machine_folder.exists() || !machine_folder.is_directory())
        throw std::logic_error("cannot access the ./user/machine folder");
}