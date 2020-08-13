//
// Created by Angelica on 30/07/2020.
//
#include <boost/locale.hpp>
#include <arpa/inet.h>
#include <filesystem>
#include <boost/algorithm/string.hpp>
#include "Configuration.h"
std::optional<Configuration> Configuration::configuration = std::nullopt;

std::optional<Configuration> Configuration::getConfiguration(std::string& filename) {
    if(!configuration.has_value()){
        std::ifstream file{filename, std::ifstream::in};
        if(!file) {
            return std::nullopt;
        }
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(file, pt);

        try{
            std::string local_path = boost::algorithm::trim_copy(pt.get<std::string>("path"));
            if(local_path.compare(local_path.size()-1,local_path.size()-1,"/") == 0 )
                local_path = local_path.substr(0, local_path.size() -1);
            std::string local_machineID = pt.get<std::string>("machineID");
            std::string local_username = pt.get<std::string>("username") ;
            std::string local_password = pt.get<std::string>("password");
            std::string local_ipAddress = pt.get<std::string>("ipAddress");
            int local_port = pt.get<int>("port");
            /*
             * if one of the expected fields is not present in the ptree
             * ( that means that it/they were not in the configuration file)
             * the boost::property_tree::ptree_bad_path is thrown
             */

            /*
             * check if username, password and machineID contains only utf8 characters
             * otherwise a conversion_error is thrown
             */
            local_username = boost::locale::conv::to_utf<char>(local_username, "UTF-8", boost::locale::conv::stop);
            local_password = boost::locale::conv::to_utf<char>(local_password, "UTF-8", boost::locale::conv::stop);
            local_machineID = boost::locale::conv::to_utf<char>(local_machineID, "UTF-8", boost::locale::conv::stop);

            //TODO add messages for format error
            if(local_username.find("/") == std::string::npos) //username should not contains a /
                if(local_machineID.find("/") == std::string::npos) {//same for machineID
                    int32_t addr;
                    if (inet_pton(AF_INET, local_ipAddress.c_str(), &addr) ==
                        1) { //if returns 1, the ip address is valid
                        std::filesystem::directory_entry dir{local_path};
                        if (dir.exists() && dir.is_directory()) { //check that the path exists and is a directory
                            if (local_port >= 0 && local_port <= 65535) //check that the port is in a valid range
                                configuration.emplace(
                                        Configuration(local_path, local_machineID, local_username, local_password,
                                                      local_ipAddress, local_port));
                                std::cout<<"Configuration loaded correctly"<<std::endl;
                        }
                    }
                }
        }
        catch ( boost::property_tree::ptree_bad_path exception) {
            /*
             * this exception is called in case the get method if the ptree
             * is called with a parameter that does not correspond
             * to any key contained in the ptree
             */
            file.close();
            std::cerr << "missing field(s) in configuration file" << std::endl;
            return std::nullopt;
        }
        catch (boost::locale::conv::conversion_error exception){
            file.close();
            std::cerr << "invalid character set used, only utf8 is allowed" << std::endl;
            return std::nullopt;
        }
        catch (...) {
            // in any other case
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




