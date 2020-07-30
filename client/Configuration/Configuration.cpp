//
// Created by Angelica on 30/07/2020.
//

#include "Configuration.h"
std::optional<Configuration> Configuration::configuration = std::nullopt;

std::optional<Configuration> Configuration::getConfiguration(std::string filename) {
    if(!configuration.has_value()){
        std::ifstream file{filename, std::ifstream::in};
        if(!file) {
            return std::nullopt;
        }
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(file, pt);

        try{
            std::string local_path = pt.get<std::string>("path");
            std::string local_machineID = pt.get<std::string>("machineID");
            std::string local_username = pt.get<std::string>("username") ;
            std::string local_password = pt.get<std::string>("password");
            std::string local_ipAddress = pt.get<std::string>("ipAddress");
            int local_port = pt.get<int>("port");

            configuration.emplace(Configuration(local_path, local_machineID, local_username, local_password, local_ipAddress, local_port));
        }
        catch ( boost::property_tree::ptree_bad_path exception) {
            file.close();
            std::cerr << "missing field(s) in configuration file" << std::endl;
            return std::nullopt;
        }
        catch (...) {
            file.close();
            std::cerr << "something wrong in configuration file" << std::endl;
            return std::nullopt;
        }
        file.close();
    }
    return configuration;
}

std::optional<Configuration> Configuration::getConfiguration() {
    return configuration;
}

Configuration::Configuration( const std::string path, const std::string machineID, const std::string username, const std::string password, const std::string ipAddress, const int port):
path(path), machineID(machineID), username(username), password(password), ipAddress(ipAddress), port(port){};

std::string Configuration::getPath() {
    return path;
}

std::string Configuration::getMachineID() {
    return machineID;
}

std::string Configuration::getUsername() {
    return username;
}

std::string Configuration::getPassword() {
    return password;
}

std::string Configuration::getIpAddress() {
    return ipAddress;
}

int Configuration::getPort() {
    return port;
}




