//
// Created by Angelica on 12/08/2020.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string/trim.hpp>
#include "workspace_utils.h"
#include "../authentication/authentication.h"

void createMachineFolder(std::string user, std::string machineID, std::string client_path);
void addNewMapping(std::string user,std::string machineID,std::string client_path,long number);

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
     * the path ./user should exists
     */
    std::filesystem::directory_entry user_folder{"./"+user};
    if(!user_folder.exists() || !user_folder.is_directory())
        throw std::runtime_error("cannot access the ./"+user+" folder");
    std::filesystem::directory_entry machine_folder{"./"+user+"/"+machineID};
    if(!machine_folder.exists()){
        createMachineFolder( user, machineID, client_path);
    }
    std::ifstream mapping("./"+user+"/"+machineID+"/mapping.txt");
    if(!mapping)
        throw std::runtime_error("cannot access the mapping file");
    std::string line;
    long number = 0;
    while(std::getline(mapping,line)) {
        auto infos = splitLine(line);
        boost::algorithm::trim(infos.first);
        boost::algorithm::trim(infos.second);
        number = std::stol(infos.second, nullptr, 10);
        if(infos.first == client_path)
            return infos.second;
    }
    mapping.close();
    number++;
    addNewMapping(user, machineID, client_path, number);
    return std::to_string(number);
}

void createMachineFolder(std::string user, std::string machineID, std::string client_path){
    std::string dir_path{"./"+user+"/"+machineID};
    std::filesystem::path dir(dir_path);
    if(!std::filesystem::create_directory(dir))
        throw std::runtime_error("Cannot create ./"+user+"/"+machineID+" folder");
    std::ofstream mapping("./"+user+"/"+machineID+"/mapping.txt");
    if(!mapping)
        throw std::runtime_error("Cannot create ./"+user+"/"+machineID+"/mapping.txt file");
    mapping << client_path+"\t1" << std::endl;
    mapping.close();
}

void addNewMapping(std::string user,std::string machineID,std::string client_path,long number){
    std::ofstream mapping("./"+user+"/"+machineID+"/mapping.txt" , std::ofstream::out | std::ofstream::app);
    if(!mapping){
        throw std::runtime_error("Cannot open ./"+user+"/"+machineID+"/mapping.txt file");
    }
    mapping << client_path+"\t"+std::to_string(number) << std::endl;
    mapping.close();
}