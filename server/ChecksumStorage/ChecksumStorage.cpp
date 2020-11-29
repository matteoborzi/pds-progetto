#include "ChecksumStorage.h"
#include <SQLiteCpp/Database.h>
#include <filesystem>
#include <SQLiteCpp/Transaction.h>
#include "../../common/Checksum.h"
#define filename "../checksum_storage.db"

/**
 * Retrieve the checksum of a file
 * @param path of the file
 * @return the checksum or nullopt
 */
std::optional <std::string> getChecksum(const std::string &path) {
    //opening the DB file
    SQLite::Database db(filename, SQLite::OPEN_READWRITE); //throws an exception if it can not be open

    SQLite::Statement query(db,
                            "SELECT checksum FROM checksum_cache WHERE path = ? ");
    query.bind(1, path);
    if (query.executeStep()) {//something returned
        std::string chk = query.getColumn(0);
        return chk;
    }
    return std::nullopt;
}

/**
 * Delete all the checksums belonging to a specified folder
 * @param path of the folder
 * @return bool indicating success
 * @throws logic_error if the directory does not exists
 */
bool deleteFolderRecursively(const std::string &path) {
    std::filesystem::directory_entry dir{path};
    if(!dir.exists())
        return false;
    try{
        //opening the DB file
        SQLite::Database db(filename, SQLite::OPEN_READWRITE); //throws an exception if it can not be open
        SQLite::Transaction transaction{db};

        //delete all entry beginning with path
        SQLite::Statement query(db,"DELETE FROM checksum_cache WHERE path LIKE ? ;");

        query.bind(1, path+"/%");
        query.exec();

        //delete folder (-r)
        std::filesystem::remove_all(path);

        //commit
        transaction.commit();
    }catch(std::exception& e) {
        return false;
    }
    return true;
}

/**
 * Insert or update the checksum of a file (which must have temporary extension),
 * overwrite (or rename) old_file with the one with temporary extension
 * @param path (Without temporary extension)
 * @return bool indicating succes
 * @throws logic_error if tmp does not exists or is a directory
 */
bool updateChecksum(const std::string &path) {
    std::string tmp_path{path+TMP_EXTENSION};
    std::filesystem::directory_entry temporary_file{tmp_path};
    if(!temporary_file.exists() || temporary_file.is_directory())
        throw std::logic_error("Expecting "+tmp_path+" to exist");
    try{
        //opening the DB file
        SQLite::Database db(filename, SQLite::OPEN_READWRITE); //throws an exception if it can not be open
        SQLite::Transaction transaction{db};

        //compute checksum
        std::string checksum= computeChecksum(tmp_path);

        //insert into DB (PK as unique CONSTRAINT ON CONFLICT REPLACE)
        SQLite::Statement insert(db, "INSERT INTO checksum_cache(path, checksum) VALUES (?, ?) ");
        insert.bind(1,path);
        insert.bind(2, checksum);

        if(insert.exec()!=1)
            return false;

        //delete old file (if exists)
        std::filesystem::directory_entry old_file{path};

        if(old_file.exists())
            std::filesystem::remove(path);

        //rename temporary file
        std::filesystem::rename(tmp_path, path);

        //commit
        transaction.commit();
    }catch(std::exception& e) {
        return false;
    }
    return true;
}
