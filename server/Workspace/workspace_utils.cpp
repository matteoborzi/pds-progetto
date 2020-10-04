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

/**
 *
 * @param user
 * @param machineID
 * @param path
 * @return true if the combination is not already present in the WORKSPACE db table, false otherwise
 */
bool isClientPathAlreadyPresent(const std::string& user, const std::string& machineID, const std::string& path){
    //opening the DB file
    SQLite::Database db(filename); //throws an exception if it can not be open
    SQLite::Statement query(db, "SELECT COUNT(*) FROM WORKSPACE WHERE username = ? AND machineID = ? AND clientPath = ? ");
    query.bind(1, user);
    query.bind(2, machineID);
    query.bind(3, path);
    if(query.executeStep()){
        int res = query.getColumn(0);
        return res != 0;
    }
    return false;
}

/**
 *
 * @param user
 * @return a set containing all pairs (machineID, clientPath) associated with the selected user
 */
std::set<std::pair<std::string, std::string>> getAvailableClientPath(const std::string& user){
    //opening the DB file
    SQLite::Database db(filename); //throws an exception if it can not be open
    std::set<std::pair<std::string, std::string>> availables{};

    SQLite::Statement query(db, "SELECT machineID, clientPath FROM WORKSPACE WHERE username = ?");
    query.bind(1, user);
    while(query.executeStep()){
        std::string machine = query.getColumn(0);
        std::string path = query.getColumn(1);
        availables.insert(std::make_pair(machine, path));
    }
    return availables;
}

bool updateMapping(const std::string &user, const std::string &oldMachineID, const std::string &oldClientPath,
                   const std::string &newMachineID, const std::string &newClientPath) {
    //opening the DB file
    SQLite::Database db(filename, SQLite::OPEN_READWRITE); //throws an exception if it can not be open

    SQLite::Statement query(db, "UPDATE WORKSPACE\n"
                                    "SET machineID = ?, clientPath = ?\n "
                                    "WHERE username = ? AND machineID = ? AND clientPath = ?");
    query.bind(1, newMachineID);
    query.bind(2, newClientPath);
    query.bind(3, user);
    query.bind(4, oldMachineID);
    query.bind(5, oldClientPath);

    int res = query.exec();

    return res==1;
}
