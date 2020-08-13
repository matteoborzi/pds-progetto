//
// Created by Angelica on 24/07/2020.
//

#include <algorithm>
#include <iostream>
#include "Directory.h"

std::shared_ptr<Directory> Directory::root = nullptr;

int Directory::myType() const {
    return DIRTYPE;
}

std::shared_ptr<Directory> Directory::getRoot() {
    if(!Directory::root){
        Directory::root = Directory::makeDirectory("/", std::shared_ptr<Directory>(nullptr));
    }
    return Directory::root;
}

std::shared_ptr<Directory> Directory::makeDirectory(const std::string& name, std::weak_ptr<Directory> parent) {
    std::shared_ptr<Directory> dir(new Directory(name));
    dir->self = dir;
    dir->parent = parent.lock();
    return dir;
}

std::shared_ptr<Directory> Directory::addDirectory(const std::string &name) {
    if(name == "." || name == ".." || this->children.find(name) != children.end())
        return std::shared_ptr<Directory>(nullptr);
    std::shared_ptr<Directory> child = Directory::makeDirectory(name, self);
    this->children.insert(std::make_pair(child->getName(), child));
    return child;
}

std::shared_ptr<DirectoryEntry> Directory::get(const std::string &name) {
    std::shared_ptr<DirectoryEntry> dir = std::shared_ptr<DirectoryEntry>(nullptr);
    if(name == ".." && this->parent.lock())
        dir = this->parent.lock();
    else if(name == ".")
        dir = this->self.lock();
    else if(this->children.find(name) != children.end()){
        dir = this->children.at(name);
    }
    return dir;
}

std::shared_ptr<File> Directory::addFile(const std::string &name, std::string checksum, long time) {
    if(name == "." || name == ".." || this->children.find(name) != children.end())
        return std::shared_ptr<File>(nullptr);
    std::shared_ptr<File> file(new File(name, checksum, time));
    children.insert(std::make_pair(file->getName(), file));
    return file;
}

bool Directory::deleteEntry(const std::string &name) {
    return this->children.erase(name) != 0;
}

std::unordered_map<std::string, std::shared_ptr<DirectoryEntry>> Directory::getNotVisited() {
    std::unordered_map<std::string, std::shared_ptr<DirectoryEntry>> notVisited{};
    for(std::pair<const std::basic_string<char>, std::shared_ptr<DirectoryEntry>> entry : this->children){
        if(!entry.second->getVisited())
            notVisited[ ( root.get() != this ? this->getName() : "") +"/" + entry.first] = entry.second;
        else if(entry.second->getVisited() && entry.second->myType() == DIRTYPE){
            std::shared_ptr<Directory> dir = std::static_pointer_cast<Directory>(entry.second);
            std::unordered_map<std::string, std::shared_ptr<DirectoryEntry>> result =dir->getNotVisited();

            std::for_each(result.begin(), result.end(), [this, &notVisited](std::pair<std::string, std::shared_ptr<DirectoryEntry>> x){
               notVisited[( root.get() != this ? this->getName() : "")+"/"+x.first] = x.second ;
            });
            //notVisited.insert(result.begin(), result.end());
        }
    }
    return notVisited;
}

void Directory::unsetVisited() {
    setVisited(false);
    for(auto & element : children)
        element.second->unsetVisited();
}




