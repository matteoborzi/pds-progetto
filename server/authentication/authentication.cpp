#include <shared_mutex>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include "authentication.h"

#define  SEPARATOR "\t"
#define filename "authentication.txt"

std::pair<std::string, std::string> splitLine(std::string s);
void addUser(std::string user, std::string pw);
void createUserFolder(std::string user);

static std::shared_mutex _authentication;


bool authenticate(std::string username, std::string password){
   std::shared_lock readL{_authentication};


    std::ifstream file{filename};
    std::string line;

    if(!file)
        throw std::runtime_error("Cannot access authentication file");
    while(std::getline(file,line)) {
        auto infos = splitLine(line);
        if (infos.first == username) {
            file.close();
            if (infos.second == password)
                return true;
            return false;
        }
    }
    file.close();
    readL.unlock();

    //getting here when user is not found, adding and authenticating him
    addUser( username, password);


    //TODO add new user folder
    createUserFolder(username);
    return true;
}

std::pair<std::string, std::string> splitLine(std::string s){
    std::vector<std::string> vec{};
    boost::split(vec, s, boost::is_any_of(SEPARATOR));

    return std::pair{vec[0] , vec[1]};
}

void addUser( std::string user, std::string pw){
    std::unique_lock l{_authentication};

    std::ofstream f{filename, std::ios::out | std::ios::app};
    if(!f)
        throw std::runtime_error("Cannot add a new user");
    //std::cout<<"Saving on file "<<user<<" "<<pw<<std::endl;
    f<<user<<SEPARATOR<<pw<<std::endl;
    f.close();
}

void createUserFolder(std::string user){
    std::string dir_path{"./"+user};
    boost::filesystem::path dir(dir_path);
    if(!boost::filesystem::create_directory(dir))
       throw std::runtime_error("Cannot create user folder");

}