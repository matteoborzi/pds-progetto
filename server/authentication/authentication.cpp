#include <shared_mutex>
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <cstddef>
#include <filesystem>
#include <crypto++/cryptlib.h>
#include <crypto++/osrng.h> 
#include <crypto++/filters.h>
#include <crypto++/hex.h>
#include <crypto++/sha.h>
#include "authentication.h"

#define  SEPARATOR "\t"
#define filename "../authentication/authentication.txt"
#define BLOCKSIZE 16 * 8

void addUser(std::string& user, std::string& pw);
void createUserFolder(std::string& user);
std::pair<std::string, std::pair<std::string, std::string>> splitLine(std::string& s);
std::string computeSaltedHash(std::string& password, std::string& salt);
std::string generateRandomSalt();

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
	std::string salt;

    if(!file)
        //file not present
        throw std::runtime_error("Cannot access authentication file");
    //reading every line
    while(std::getline(file,line)) {
        //extracting username, hashed password and salt for each line
        auto infos = splitLine(line);
        boost::algorithm::trim(infos.first);
        boost::algorithm::trim(infos.second.first);
		boost::algorithm::trim(infos.second.second);
		salt = infos.second.second;
8
		if (infos.first == username) {
            //same username, search ended
            file.close();

            //if a full match is found, authenticating the user
            if (computeSaltedHash(password, infos.second.second) == infos.second.first)
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
 * @return pair with <username, <password, salt>>
 */
std::pair<std::string, std::pair<std::string, std::string>> splitLine(std::string& s){
    std::vector<std::string> vec{};
    boost::split(vec, s, boost::is_any_of(SEPARATOR));
	return std::pair{ vec[0] , std::pair{vec[1], vec[2]} };
}

/**
 * Add a new user to the DB file
 * @param user
 * @param password
 */
void addUser( std::string& user, std::string& pw){
    //write lock must be unique
    std::unique_lock l{_authentication};
    //opening the file
    std::ofstream f{filename, std::ios::out | std::ios::app};
    if(!f)
        throw std::runtime_error("Cannot add a new user");

	//generate a new unique salt for the user
	std::string salt{generateRandomSalt()};
	std::string hashedPassword{ computeSaltedHash(pw,salt) };

	//adding informations
    f<<user<<SEPARATOR<<hashedPassword<<SEPARATOR<<salt<<std::endl;
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

/**
 *	Compute the password hash using the password and the stored salt
 *	@param password
 *	@param salt
 *	@returns a string containing the salted hash of the password
 */
std::string computeSaltedHash( std::string& password, std::string& salt) {
	std::string msg = password + salt;
	std::string digest;
	CryptoPP::SHA256 hash;

	CryptoPP::StringSource s(msg, true,
			new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	return digest;
}

/**
 * Generate a cryptographically secure random salt 
 * @returns a string containing the random salt as a string encoded in hexadecimal
 */
std::string generateRandomSalt() {
	unsigned char pcbScratch[BLOCKSIZE];
	std::string salt;

	CryptoPP::AutoSeededRandomPool rng;
	rng.GenerateBlock(pcbScratch, BLOCKSIZE);

	CryptoPP::StringSource ss(pcbScratch, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(salt)));

	return salt;
}
