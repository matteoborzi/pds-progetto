#include <shared_mutex>
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <cstddef>
#include <filesystem>
#include <crypto++/osrng.h> 
#include <crypto++/filters.h>
#include <crypto++/hex.h>
#include <crypto++/sha.h>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>
#include <boost/asio/ip/tcp.hpp>
#include "authentication.h"
#include "../../common/messages/AuthenticationRequest.pb.h"
#include "../../common/messages/AuthenticationResponse.pb.h"
#include "../../common/messages/socket_utils.h"

#define filename "../authentication.db"
#define BLOCKSIZE 16 * 8

bool authenticate(std::string username, std::string password);
bool addUser(std::string& user, std::string& pw, SQLite::Database& db);
std::string computeSaltedHash(std::string& password, std::string& salt);
std::string generateRandomSalt();



//user informations are stored in the table USER(username, salt, hash)
//in the authentication.db file

std::optional<std::string> doAuthentication(boost::asio::ip::tcp::socket& s){

    BackupPB::AuthenticationRequest authenticationRequest;
    BackupPB::AuthenticationResponse authenticationResponse;
    std::optional<std::string> username;

    try{
        authenticationRequest = readFromSocket<BackupPB::AuthenticationRequest>(s);
    } catch(std::exception& e) {
        std::cerr<< e.what() << std::endl;
        return std::nullopt;
    }

    if(!authenticate(authenticationRequest.username(), authenticationRequest.password())){
        //std::cerr << "Login failed" << std::endl;
        authenticationResponse.set_status(BackupPB::AuthenticationResponse_Status_FAIL);
        username = std::nullopt;
    } else {
        authenticationResponse.set_status(BackupPB::AuthenticationResponse_Status_OK);
        username = authenticationRequest.username();
    }

    try{
        writeToSocket(s, authenticationResponse);
    } catch(std::exception& e){
        std::cerr << e.what() << std::endl;
        return std::nullopt;
    }

    return username;
}


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

        if(addUser( username, password, db))
            return true;
        return false;
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

	CryptoPP::StringSource ss(pcbScratch, BLOCKSIZE, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(salt)));

	return salt;
}
