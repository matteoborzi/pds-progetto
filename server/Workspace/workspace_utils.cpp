//
// Created by Angelica on 12/08/2020.
//

#include <filesystem>
#include <iostream>
#include "workspace_utils.h"
#include <boost/algorithm/string.hpp>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>
#include <SQLiteCpp/Transaction.h>

#define filename "../mapping.db"

std::pair<std::string, std::string> splitLineWorkspace(std::string& s);
void createMachineFolder(std::string user, std::string machineID);
std::string addNewMapping(std::string user,std::string machineID,std::string client_path, SQLite::Database& db);

//workspaces' mappings are inside the table WORKSPACE(username*, machineID*, clientPath*, serverPath)
//in the db mapping.db

/**
 * this function should be called to retrieve,
 * basing on
 * @param username
 * @param machineID
 * @param client absolute path of the folder,
 * the server path where the user's folder is copied
 */
std::string computeServerPath(std::string user, std::string machineID, std::string client_path){

    //opening the DB file
    SQLite::Database db(filename, SQLite::OPEN_READWRITE); //throws an exception if it can not be open

    // the path ./user should exists
    std::filesystem::directory_entry user_folder{"./"+user};
    if(!user_folder.exists() || !user_folder.is_directory())
        throw std::runtime_error("cannot access the ./"+user+" folder");

    //check if the combination user-machineID already exists in the db as long as the /user/machineID folder
    SQLite::Statement query(db, "SELECT COUNT(*) FROM WORKSPACE WHERE username = ? AND machineID = ? ");
    query.bind(1, user);
    query.bind(2, machineID);
    int n = 0;
    if(query.executeStep()) //if true, something returned
        n = query.getColumn(0);

    std::filesystem::directory_entry machine_folder{"./"+user+"/"+machineID};

    if(!machine_folder.exists() && n > 0){
       //inconsistencies between db and folders
       std::string msg = "inconsistencies in folders: folder ./"+user+"/"+machineID+" should exists but it doesn't";
       throw std::runtime_error(msg);
    }
    else if(machine_folder.exists() && n == 0){
        std::string msg = "inconsistencies in folders: folder ./"+user+"/"+machineID+" should NOT exists but it does";
        throw std::runtime_error(msg);
    }
    else if(n == 0){
        createMachineFolder(user, machineID);
    }
    else {
        SQLite::Statement query(db,
                                "SELECT serverPath FROM WORKSPACE WHERE username = ? AND machineID = ? AND clientPath = ? ");
        query.bind(1, user);
        query.bind(2, machineID);
        query.bind(3, client_path);
        if (query.executeStep()) {//something returned
            std::string server_path = query.getColumn(0);
            return "/" + user + "/" + machineID + "/" + server_path + "/";
        }
    }
    //if the function arrives here, the mapping is not already present
    // (but the folder /user/machineID should be present)
    SQLite::Transaction transaction{db};
    std::string server_path = addNewMapping(user, machineID, client_path, db);
    createServerFolder(user, machineID, server_path);
    //TODO add also directory number_cache
    transaction.commit();
    return "/"+user+"/"+machineID+"/"+server_path+"/";
}

/**
 * this function receives
 * @param username
 * @param machineID
 * and creates the folder ./user/machineID
 * if something goes wrong, it throws an excwption
 */
void createMachineFolder(std::string user, std::string machineID){
    std::string dir_path{"./"+user+"/"+machineID};
    std::filesystem::path dir(dir_path);
    if(!std::filesystem::create_directory(dir))
        throw std::runtime_error("Cannot create ./"+user+"/"+machineID+" folder");
}

std::string addNewMapping(std::string user,std::string machineID,std::string client_path, SQLite::Database& db){

    SQLite::Statement insert(db, "INSERT INTO WORKSPACE (username, machineID, clientPath) VALUES (?, ?, ?) ");
    insert.bind(1, user);
    insert.bind(2, machineID);
    insert.bind(3, client_path);
    int res = insert.exec();

    if(res != 1)
        throw std::runtime_error("Cannot create new mapping for backup folder "+client_path+" at ./"+user+"/"+machineID);
    SQLite::Statement query(db, "SELECT serverPath FROM WORKSPACE WHERE username = ? AND machineID = ? AND clientPath = ? ");
    query.bind(1, user);
    query.bind(2, machineID);
    query.bind(3, client_path);
    if(query.executeStep()){
        std::string server_path = query.getColumn(0);
        return server_path;
    }
    else{
        //something went wrong in inserting/retrieving serverPath information from db
        throw std::runtime_error("Unable to create new mapping for backup folder "+client_path+" at ./"+user+"/"+machineID);
    }
}

/**
* Split each line of the DB file
* @param line
* @return pair with <username, password>
*/
std::pair<std::string, std::string> splitLineWorkspace(std::string& s){
    std::vector<std::string> vec{};
    boost::split(vec, s, boost::is_any_of(SEPARATOR));
    return std::pair{vec[0] , vec[1]};
}