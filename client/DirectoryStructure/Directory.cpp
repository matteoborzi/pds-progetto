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

/**
 * Method to retrieve the instance of the root of DirectoryStructure (constructing it if not present)
 * @return the root
 */
std::shared_ptr<Directory> Directory::getRoot() {
    if(!Directory::root){
        Directory::root = Directory::makeDirectory("/", std::shared_ptr<Directory>(nullptr));
    }
    return Directory::root;
}

/**
 * Create a new directory object
 * @param name of the new directory
 * @param parent as weak pointer
 * @return
 */
std::shared_ptr<Directory> Directory::makeDirectory(const std::string& name, std::weak_ptr<Directory> parent) {
    std::shared_ptr<Directory> dir(new Directory(name));
    dir->self = dir;
    dir->parent = parent.lock();
    return dir;
}

/**
 * Add a directory to the current directory starting from the whole name
 * @param name of the folder
 * @return the pointer to the directory created or nullptr
 */
std::shared_ptr<Directory> Directory::addDirectory(const std::string &name) {
    //name not valid or already present in the current folder
    if(name == "." || name == ".." || this->children.find(name) != children.end())
        return std::shared_ptr<Directory>(nullptr);
    //create the instance
    std::shared_ptr<Directory> child = Directory::makeDirectory(name, self);
    //inserting in children list
    this->children.insert(std::make_pair(child->getName(), child));
    return child;
}

/**
 * Retrieve a direct child given its name
 * @param name
 * @return the pointer to the child or nullptr
 */
std::shared_ptr<DirectoryEntry> Directory::get(const std::string &name) {
    std::shared_ptr<DirectoryEntry> dir = std::shared_ptr<DirectoryEntry>(nullptr);
    //getting the parent
    if(name == ".." && this->parent.lock())
        dir = this->parent.lock();
    //getting current directory
    else if(name == ".")
        dir = this->self.lock();
    //searching between children (if present)
    else if(this->children.find(name) != children.end()){
        dir = this->children.at(name);
    }
    return dir;
}

/**
 * Add a file to the current directory
 * @param name
 * @param checksum
 * @param time
 * @param size
 * @return the pointer to the file
 */
std::shared_ptr<File> Directory::addFile(const std::string &name, std::string checksum, long time, size_t size) {
    //name not valid or already present
    if(name == "." || name == ".." || this->children.find(name) != children.end())
        return std::shared_ptr<File>(nullptr);
    //creating the instance of the file
    std::shared_ptr<File> file(new File(name, checksum, time, size));
    children.insert(std::make_pair(file->getName(), file));
    return file;
}

/**
 * Delete a child with a given name
 * @param name
 * @return true on success
 */
bool Directory::deleteEntry(const std::string &name) {
    return this->children.erase(name) != 0;
}

/**
 * Returns the list of children that has not been visited (during a scan)
 * @return a map <name, pointer>
 */
std::unordered_map<std::string, std::shared_ptr<DirectoryEntry>> Directory::getNotVisited() {
    std::unordered_map<std::string, std::shared_ptr<DirectoryEntry>> notVisited{};
    for(std::pair<const std::basic_string<char>, std::shared_ptr<DirectoryEntry>> entry : this->children){
        // the child has not been visited
        if(!entry.second->getVisited())
            //adding it to the result map ( adding current directory's name)
            notVisited[ ( root.get() != this ? this->getName() : "") +"/" + entry.first] = entry.second;
        else if(entry.second->getVisited() && entry.second->myType() == DIRTYPE){
            //the element is a directory, but has been visited
            std::shared_ptr<Directory> dir = std::static_pointer_cast<Directory>(entry.second);

            //getting the elements that have not been visited in the child dircectory
            std::unordered_map<std::string, std::shared_ptr<DirectoryEntry>> result =dir->getNotVisited();

            //copying in the result
            std::for_each(result.begin(), result.end(), [this, &notVisited](std::pair<std::string, std::shared_ptr<DirectoryEntry>> x){
               notVisited[( root.get() != this ? this->getName() : "")+"/"+x.first] = x.second ;
            });
            //notVisited.insert(result.begin(), result.end());
        }
    }
    return notVisited;
}

/**
 * Marks all children element and itself as not visited
 */
void Directory::unsetVisited() {
    setVisited(false);
    for(auto & element : children)
        element.second->unsetVisited();
}




