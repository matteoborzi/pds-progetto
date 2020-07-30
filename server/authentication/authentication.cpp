#include <shared_mutex>
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <filesystem>
#include "authentication.h"

#define  SEPARATOR "\t"
#define filename "../authentication/authentication.txt"

std::pair<std::string, std::string> splitLine(std::string& s);
void addUser(std::string& user, std::string& pw);
void createUserFolder(std::string& user);

static std::shared_mutex _authentication;

/**
 * Function to authenticate a user. The user is also added whether the username is not yet present in the list
 * @param username
 * @param password
 * @return boolean to indicate if the user will be authenticated
 * @throws runtime_error when error in retrieving or adding user
 */
bool authenticate(std::string username, std::string password){
   // threads can read concurrently the file
   std::shared_lock readL{_authentication};

    //opening the "DB" file
    std::ifstream file{filename};
    std::string line;

    if(!file)
        //file not present
        throw std::runtime_error("Cannot access authentication file");
    //reading every line
    while(std::getline(file,line)) {
        //extracting username and password for each line
        auto infos = splitLine(line);
        if (infos.first == username) {
            //same username, search ended
            file.close();

            //if a full match is found, authenticating the user
            if (infos.second == password)
                return true;
            return false;
        }
    }
    file.close();
    readL.unlock();

    //getting here when user is not found, adding and authenticating him
    addUser( username, password);
    //creating user folder
    createUserFolder(username);
    return true;
}

/**
 * Split each line of the DB file
 * @param line
 * @return pair with <username, password>
 */
std::pair<std::string, std::string> splitLine(std::string& s){
    std::vector<std::string> vec{};
    boost::split(vec, s, boost::is_any_of(SEPARATOR));
    return std::pair{vec[0] , vec[1]};
}

/**
 * Add a new user to the DB file
 * @param user
 * @param pw
 */
void addUser( std::string& user, std::string& pw){
    //write lock must be unique
    std::unique_lock l{_authentication};
    //opening the file
    std::ofstream f{filename, std::ios::out | std::ios::app};
    if(!f)
        throw std::runtime_error("Cannot add a new user");
    //adding informations
    f<<user<<SEPARATOR<<pw<<std::endl;
    if(!f)
        throw std::runtime_error("Something goes wrong while saving the user");
    f.close();
}

/**
 * Create an empty folder for a new user
 * @param user to create the folder
 */
void createUserFolder(std::string& user){
    std::string dir_path{"./"+user};
    std::filesystem::path dir(dir_path);
    if(!std::filesystem::create_directory(dir))
       throw std::runtime_error("Cannot create user folder");

}