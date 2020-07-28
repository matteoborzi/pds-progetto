//
// Created by Angelica on 28/07/2020.
//

#include "utils.h"

std::shared_ptr<Directory> getParent(std::string& path){
    return nullptr;
}

bool deleteDirectoryOrFile(std::string &path) {
    std::shared_ptr<Directory> parent = getParent(path);
    std::string toDelete = getLast(path);
    parent->deleteEntry(toDelete);
    return false;
}

bool addDirectory(std::string& path){
    return false;
}

bool addFile(std::string& path){
    return false;
}

bool addFile(std::string& path, std::string& checksum, long time){
return false;
}

std::shared_ptr<Directory> getDirectory(std::string& path){
return nullptr;
}

std::shared_ptr<File> getFile(std::string& path){
return nullptr;
}

std::string getLast(std::string& path){
    std::vector<std::string> fields{};
    boost::split(fields, path, boost::is_any_of("/"));
    return fields.back();
}