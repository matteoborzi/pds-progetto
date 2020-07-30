//
// Created by Angelica on 30/07/2020.
//

#ifndef CLIENT_CONFIGURATION_H
#define CLIENT_CONFIGURATION_H

#include <string>
#include <fstream>
#include <iostream>
#include <optional>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

/* this class implements the singleton pattern
 * the configuration field contains the unique reference to that object
 * the getConfiguration methods return that field and (eventually) initialize it
 */

class Configuration {
private:
    static std::optional<Configuration> configuration;
    Configuration( const std::string path, const std::string machineID, const std::string username, const std::string password, const std::string ipAddress, const int port);
    std::string path;
    std::string machineID;
    std::string username;
    std::string password;
    std::string ipAddress;
    int port;
public:
    Configuration(const std::string &machineId);

    static std::optional<Configuration> getConfiguration(std::string filename);
    static std::optional<Configuration> getConfiguration();

    std::string getPath();
    std::string getMachineID();
    std::string getUsername();
    std::string getPassword();
    std::string getIpAddress();
    int getPort();

};

#endif //CLIENT_CONFIGURATION_H
