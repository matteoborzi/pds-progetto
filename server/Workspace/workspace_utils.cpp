#include <filesystem>
#include "workspace_utils.h"
#include "../ChecksumStorage/ChecksumStorage.h"
#include "../../common/fieldValidation.h"
#include <boost/algorithm/string.hpp>
#include <SQLiteCpp/Database.h>
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

    if(!validateFieldFormat(machineID)){
        throw std::runtime_error("Invalid character set used for machineID, only utf8 is allowed");
    }

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

/**
 * This function generates a new entry in the Workspace DB
 * and maps that entry on the server filesystem
 * @param user
 * @param machineID
 * @param client_path
 * @param db
 * @return server_path string corresponding to the entry
 */
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

/**
 * This function creates the actual folder in the server filesystem
 * @param server_path
 */
void createServerFolder(std::string server_path){
    std::string dir_path{"./"+server_path};
    std::filesystem::path dir(dir_path);
    if(!std::filesystem::create_directory(dir))
        throw std::runtime_error("Cannot create ./"+server_path+" folder");
}

/**
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

/**
 * Re-map a (machineId,path) pair for a certain user to a new pair.
 * Used for restore purposes.
 * @param user
 * @param oldMachineID
 * @param oldClientPath
 * @param newMachineID
 * @param newClientPath
 * @return true if update is successful
 */
bool updateMapping(const std::string &user, const std::string &oldMachineID, const std::string &oldClientPath,
                   const std::string &newMachineID, const std::string &newClientPath) {
    // Opening the DB file
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

/**
 * This function scans recursively a certain path and checks the presence of temporary files.
 *  If there is a temp file but not the relative regular file, the
 * @param path
 */
void cleanFileSystem(const std::string& path){
    std::filesystem::directory_entry dir{path};
    if(!dir.exists() || !dir.is_directory())
        throw std::runtime_error(path+" not existing in the file system");

    for(std::filesystem::directory_entry element : std::filesystem::recursive_directory_iterator(path)) {
        // Scan recursively all files in path
        std::string file_path{element.path().string()};

        // Check presence of temp files
        if(element.is_regular_file() && boost::algorithm::ends_with(element.path().string(), TMP_EXTENSION)) {
            boost::algorithm::erase_last(file_path, std::string{TMP_EXTENSION});

            std::filesystem::directory_entry old{file_path};
            // If temp file is present and normal is not present, update the checksum
            if(!old.exists())
                updateChecksum(file_path);
            else
                // If both are present keep older
                std::filesystem::remove(file_path+TMP_EXTENSION);
        }
    }
}
