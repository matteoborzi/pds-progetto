#ifndef SERVER_AUTHENTICATION_H
#define SERVER_AUTHENTICATION_H

#include <string>

bool authenticate(std::string username, std::string password);
std::pair<std::string, std::pair<std::string, std::string>> splitLine(std::string& s);

#endif //SERVER_AUTHENTICATION_H
