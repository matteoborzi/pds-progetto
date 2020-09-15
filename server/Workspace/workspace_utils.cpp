//
// Created by Angelica on 12/08/2020.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string/trim.hpp>
#include "workspace_utils.h"
#include <boost/algorithm/string.hpp>

#define  SEPARATOR "\t"

void createMachineFolder(std::string user, std::string machineID, std::string client_path);
void addNewMapping(std::string user,std::string machineID,std::string client_path,long number);
std::pair<std::string, std::string> splitLineWorkspace(std::string& s);

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
        auto infos = splitLineWorkspace(line);
        boost::algorithm::trim(infos.first);
        boost::algorithm::trim(infos.second);
        number = std::stol(infos.second, nullptr, 10);
        if(infos.first == client_path){
            std::filesystem::directory_entry folder{"./"+user+"/"+machineID+"/"+infos.second};
            if(!folder.exists() || !folder.is_directory())
                throw std::runtime_error("Backup folder ./"+user+"/"+machineID+"/"+infos.second+"does not exists");
            return "/"+user+"/"+machineID+"/"+infos.second+"/";
        }
    }
    mapping.close();
    number++;
    addNewMapping(user, machineID, client_path, number);
    return "/"+user+"/"+machineID+"/"+std::to_string(number)+"/";
}

void createMachineFolder(std::string user, std::string machineID, std::string client_path){
    std::string dir_path{"./"+user+"/"+machineID};
    std::filesystem::path dir(dir_path);
    if(!std::filesystem::create_directory(dir))
        throw std::runtime_error("Cannot create ./"+user+"/"+machineID+" folder");
    std::ofstream mapping("./"+user+"/"+machineID+"/mapping.txt");
    if(!mapping)
        throw std::runtime_error("Cannot create ./"+user+"/"+machineID+"/mapping.txt file");
    std::filesystem::path newdir("./"+user+"/"+machineID+"/1");
    if(!std::filesystem::create_directory(newdir))
        throw std::runtime_error("Cannot create new backup folder");
    mapping << client_path+"\t1" << std::endl;
    mapping.close();
}

void addNewMapping(std::string user,std::string machineID,std::string client_path,long number){
    std::ofstream mapping("./"+user+"/"+machineID+"/mapping.txt" , std::ofstream::out | std::ofstream::app);
    if(!mapping){
        throw std::runtime_error("Cannot open ./"+user+"/"+machineID+"/mapping.txt file");
    }
    std::filesystem::path newdir("./"+user+"/"+machineID+"/"+std::to_string(number));
    if(!std::filesystem::create_directory(newdir))
        throw std::runtime_error("Cannot create new backup folder");
    mapping << client_path+"\t"+std::to_string(number) << std::endl;
    mapping.close();
}

/**
* Split each line of the DB file
* @param line
* @return pair with <username, password>
*/
std::pair<std::string, std::string> splitLineWorkspace(std::string& s){
    std::vector<std::string> vec{};
    boost::split(vec, s, boost::is_any_of(SEPARATOR));
    return std::pair{vec[0] , vec[1]};
}