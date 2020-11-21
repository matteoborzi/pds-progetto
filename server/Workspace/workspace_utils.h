#ifndef CLIENT_WORKSPACE_UTILS_H
#define CLIENT_WORKSPACE_UTILS_H

#include <string>
#include <set>

void cleanFileSystem(const std::string& );
std::string computeServerPath(std::string user, std::string machineID, std::string client_path);
bool isClientPathAlreadyPresent(const std::string& user, const std::string& machineID, const std::string& path);
std::set<std::pair<std::string, std::string>> getAvailableClientPath(const std::string& user);
bool updateMapping(const std::string& user, const std::string& oldMachineID, const std::string& oldClientPath, const std::string& newMachineID, const std::string& newClientPath);

#endif //CLIENT_WORKSPACE_UTILS_H
