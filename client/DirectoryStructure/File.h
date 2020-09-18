//
// Created by Angelica on 24/07/2020.
//

#ifndef CLIENT_FILE_H
#define CLIENT_FILE_H

#include "DirectoryEntry.h"
#include <filesystem>
#include <mutex>
#include <shared_mutex>

class File: public DirectoryEntry {
private:
    std::string checksum;
    std::shared_mutex checksum_mutex;
    //the checksum is the only field accessed by multiple threads
    std::time_t lastEditTime;
    //TODO add size
public:
    File(std::string name, std::string checksum, long time): DirectoryEntry(name), checksum(checksum), lastEditTime(time){};
    int myType () const;
    void setChecksum(std::string);
    void setLastEditTime(std::time_t);
    std::string getChecksum();

    time_t getLastEditTime();
};

#endif //CLIENT_FILE_H