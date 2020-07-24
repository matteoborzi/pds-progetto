#include <fstream>
#include <shared_mutex>
#include "authentication.h"

std::pair<std::string, std::string> splitLine(std::string s);
void addUser(std::fstream f, std::string user, std::string pw);

static std::shared_mutex _authentication;

bool authenticate(std::string username, std::string password){
   std::shared_lock readL{_authentication};

    std::fstream file{"authentication.txt", std::ios::in | std::ios::out | std::ios::app};
    std::string line;


    while(std::getline(file,line)) {
        auto infos = splitLine(line);
        if (infos.first == username) {
            file.close();
            if (infos.second == password)
                return true;
            return false;
        }
    }

    readL.unlock();
    //getting here when user is not found, adding and authenticating him
    file << username <<  "\t" << password  << std::endl;
    file.close();
    return true;
}

std::pair<std::string, std::string> splitLine(std::string s){
    return std::pair{"pippo", "password"};
}

void addUser(std::fstream f, std::string user, std::string pw){
    std::unique_lock l{_authentication};

    

}