//
// Created by Angelica on 24/07/2020.
//

#include "File.h"

std::string File::computeChecksum() {
    return std::string();
    //this function should call the computeChecksum function
}

void File::setLastEditTime(std::time_t last) {
    this->lastEditTime = last;
}

void File::setChecksum(std::string checksum) {
    this->checksum = checksum;
}

int File::myType() const {
    return FILETYPE;
}
