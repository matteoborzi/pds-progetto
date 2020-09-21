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

std::string addNewMapping(std::string user,std::string machineID,std::string client_path, SQLite::Database& db);
void createServerFolder(std::string server_path);

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

    SQLite::Statement query(db,
                                "SELECT serverPath FROM WORKSPACE WHERE username = ? AND machineID = ? AND clientPath = ? ");
    query.bind(1, user);
    query.bind(2, machineID);
    query.bind(3, client_path);
    if (query.executeStep()) {//something returned
       std::string server_path = query.getColumn(0);
       return server_path + "/";
    }

    //if the function arrives here, the mapping is not already present
    SQLite::Transaction transaction{db};
    std::string server_path = addNewMapping(user, machineID, client_path, db);
    createServerFolder(server_path);
    transaction.commit();
    return server_path + "/";
}


std::string addNewMapping(std::string user,std::string machineID,std::string client_path, SQLite::Database& db){

    SQLite::Statement insert(db, "INSERT INTO WORKSPACE (username, machineID, clientPath) VALUES (?, ?, ?) ");
    insert.bind(1, user);
    insert.bind(2, machineID);
    insert.bind(3, client_path);
    int res = insert.exec();

    if(res != 1)
        throw std::runtime_error("Cannot create new mapping for backup folder "+client_path+" of user "+user+" with machineID "+machineID);
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

void createServerFolder(std::string server_path){
    std::string dir_path{"./"+server_path};
    std::filesystem::path dir(dir_path);
    if(!std::filesystem::create_directory(dir))
        throw std::runtime_error("Cannot create ./"+server_path+" folder");
}
