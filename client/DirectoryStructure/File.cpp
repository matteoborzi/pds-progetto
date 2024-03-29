#include "File.h"

void File::setLastEditTime(std::time_t last) {
    this->lastEditTime = last;
}

void File::setChecksum(std::string checksum) {
    std::unique_lock l(checksum_mutex);
    this->checksum = checksum;
}

std::string File::getChecksum(){
    //checksum can be accessed by multiple threads
    std::shared_lock l(checksum_mutex);
    return this->checksum;
}

time_t File::getLastEditTime() {
    return this->lastEditTime;
}

int File::myType() const {
    return FILETYPE;
}

void File::setSize(std::size_t size) {
    this->size = size;
}

std::size_t File::getSize() {
    return this->size;
}
