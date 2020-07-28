//
// Created by Angelica on 24/07/2020.
//

#ifndef CLIENT_FILE_H
#define CLIENT_FILE_H

#include "DirectoryEntry.h"
#include <filesystem>

class File: public DirectoryEntry {
private:
    std::string checksum;
    std::time_t lastEditTime;
public:
    File(std::string name, std::string checksum, long time): DirectoryEntry(name), checksum(checksum), lastEditTime(time){};
    int myType () const;
    void setChecksum(std::string);
    void setLastEditTime(std::time_t);
    std::string getChecksum();

    time_t getLastEditTime();
};


#endif //CLIENT_FILE_H
