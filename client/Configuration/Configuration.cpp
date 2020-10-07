//
// Created by Angelica on 30/07/2020.
//
#include <boost/locale.hpp>
#include <arpa/inet.h>
#include <filesystem>
#include <boost/algorithm/string.hpp>
#include "Configuration.h"

#define MAX_PORT 65535

std::optional<Configuration> Configuration::configuration = std::nullopt;

void printCorrectConfFile();

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
            //if path is NOT "/" and ends with "/", the "/" is removed
            if(local_path!="/" && local_path.compare(local_path.size()-1,1,"/") == 0 )
                local_path = local_path.substr(0, local_path.size() -1);
            //TODO implement checks for path containing \ on Windows

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
            

            bool error= false;
            if(!local_username.find("/") == std::string::npos) {//username should not contains a /
                std::cerr<<"Name should not contain /"<<std::endl;
                error=true;
            }

            if(!local_machineID.find("/") == std::string::npos) {//same for machineID
                std::cerr<<"MachineID should not contain /"<<std::endl;
                error=true;
            }

            int32_t addr;
            if (inet_pton(AF_INET, local_ipAddress.c_str(), &addr) !=1) { //if returns 1, the ip address is valid
                std::cerr<<"Wrong IP address format, only IPv4 accepted"<<std::endl;
                error=true;
            }

            std::filesystem::directory_entry dir{local_path};
            if (!(dir.exists() && dir.is_directory())) { //check that the path exists and is a directory
                std::cerr<<"Directory to backup or restore does not exists"<<std::endl;
                error=true;
            }

            if (!(local_port > 0 && local_port <= MAX_PORT)){//check that the port is in a valid range
                std::cerr<<"Port is not in a valid range "<<std::endl;
                error=true;
            }

            if(!error) {
                configuration.emplace(
                        Configuration(local_path, local_machineID, local_username, local_password,
                                      local_ipAddress, local_port));
                std::cout << "Configuration loaded correctly" << std::endl;
            }else printCorrectConfFile();
        }
        catch ( boost::property_tree::ptree_bad_path exception) {
            /*
             * this exception is called in case the get method if the ptree
             * is called with a parameter that does not correspond
             * to any key contained in the ptree
             */
            file.close();
            std::cerr << "missing field(s) in configuration file" << std::endl;
            printCorrectConfFile();
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
            printCorrectConfFile();
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

std::string& Configuration::getPath() {
    return path;
}

std::string& Configuration::getMachineID() {
    return machineID;
}

std::string& Configuration::getUsername() {
    return username;
}

std::string& Configuration::getPassword() {
    return password;
}

std::string& Configuration::getIpAddress() {
    return ipAddress;
}

int Configuration::getPort() {
    return port;
}

void printCorrectConfFile() {
    std::cerr<<"Correct file format:"<<std::endl;
    
    std::cerr<<"{\n"
               "  \"path\": absolute_path,\n"
               "  \"username\": string,\n"
               "  \"machineID\": string,\n"
               "  \"ipAddress\": IPv4 address string,\n"
               "  \"password\": string,\n"
               "  \"port\": number [1-"<<MAX_PORT<<"]\n"
               "}"<<std::endl;
}




