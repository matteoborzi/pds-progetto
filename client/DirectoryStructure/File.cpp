//
// Created by Angelica on 24/07/2020.
//

#include "File.h"

void File::setLastEditTime(std::time_t last) {
    this->lastEditTime = last;
}

void File::setChecksum(std::string checksum) {
    this->checksum = checksum;
}

std::string File::getChecksum(){
    return this->checksum;
}

time_t File::getLastEditTime() {
    return this->lastEditTime;
}

int File::myType() const {
    return FILETYPE;
}
