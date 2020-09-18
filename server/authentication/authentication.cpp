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
#include <SQLiteCpp/Database.h>
#include "authentication.h"

#define  SEPARATOR "\t"
#define filename "../authentication/authentication.db"
#define BLOCKSIZE 16 * 8

bool addUser(std::string& user, std::string& pw, SQLite::Database& db);
bool createUserFolder(std::string& user);
std::pair<std::string, std::pair<std::string, std::string>> splitLine(std::string& s);
std::string computeSaltedHash(std::string& password, std::string& salt);
std::string generateRandomSalt();


//TODO tabella USER(username, salt, hash)
//TO EDIT: authenticate, addUser

/**
 * Function to authenticate a user. The user is also added whether the username is not yet present in the list
 * @param username
 * @param password
 * @return boolean to indicate if the user will be authenticated
 * @throws runtime_error when error in retrieving or adding user
 */
bool authenticate(std::string username, std::string password){

    //opening the DB file
    SQLite::Database db(filename, SQLite::OPEN_READWRITE); //throws an exception if it can not be open
    //compile an SQL query and bind it with the parameter
    SQLite::Statement query(db, "SELECT * FROM USER WHERE username = ?");
    query.bind(1, username);
    if(query.executeStep()) {
        //if true, one (or more) row have been retrieved
        //in this case only one, since username is primary key

        //extracting hashed password and salt
        std::string salt = query.getColumn(1);
        std::string hash = query.getColumn(2);

        //if a full match is found, authenticating the user
        if (computeSaltedHash(password, salt) == hash)
            return true;
        return false; //the password is not correct
    }
    else{
        //there are no corresponding rows for that username, so a new one is added
        //and a new user folder is created
        return addUser( username, password, db) and createUserFolder(username);
    }
}

/**
 * Add a new user to the DB file
 * @param user
 * @param password
 */
bool addUser( std::string& user, std::string& pw, SQLite::Database& db){

	//generate a new unique salt for the user
	std::string salt{generateRandomSalt()};
	std::string hashedPassword{ computeSaltedHash(pw,salt) };

	//adding informations
    SQLite::Statement query(db, "INSERT INTO USER (username, salt, hash) VALUES (?, ?, ?)");
    query.bind(1, user);
    query.bind(2, salt);
    query.bind(3, hashedPassword);
    int res = 0;
    try{
        res = query.exec(); //returns the number of modified rows
    }
    catch(...){
        //something wrong with the query
        return false;
    }
    return res==1;
}

/**
 * Create an empty folder for a new user
 * @param user to create the folder
 */
bool createUserFolder(std::string& user){
    std::string dir_path{"./"+user};
    std::filesystem::path dir(dir_path);
    if(!std::filesystem::create_directory(dir)){
        std::cerr << "Cannot create user folder" << std::endl;
        return false;
    }
    return true;
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

	CryptoPP::StringSource ss(pcbScratch, BLOCKSIZE, new CryptoPP::HexEncoder(new CryptoPP::StringSink(salt)));

	return salt;
}
