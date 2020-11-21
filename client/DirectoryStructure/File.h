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
    std::size_t size;
public:
    File(std::string name, std::string checksum, long time, std::size_t size): DirectoryEntry(name), checksum(checksum), lastEditTime(time), size(size){};
    int myType () const;
    void setChecksum(std::string);
    void setLastEditTime(std::time_t);
    std::string getChecksum();
    time_t getLastEditTime();
    void setSize(std::size_t);
    std::size_t getSize();

};

#endif //CLIENT_FILE_H