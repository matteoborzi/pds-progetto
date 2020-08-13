//
// Created by Angelica on 24/07/2020.
//

#ifndef CLIENT_DIRECTORY_H
#define CLIENT_DIRECTORY_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "DirectoryEntry.h"
#include "File.h"

class Directory: public DirectoryEntry {
    static std::shared_ptr<Directory> root;
    std::weak_ptr<Directory> parent;
    std::weak_ptr<Directory> self;
    std::unordered_map<std::string, std::shared_ptr<DirectoryEntry>> children;

    Directory(std::string dirname):DirectoryEntry(dirname), children(){};

public:
    bool deleteEntry(const std::string& name);
    std::unordered_set<std::string> getNotVisited();
    static std::shared_ptr<Directory> makeDirectory(const std::string& name, std::weak_ptr<Directory> parent);
    static std::shared_ptr<Directory> getRoot();
    std::shared_ptr<Directory> addDirectory (const std::string& name);
    std::shared_ptr<DirectoryEntry> get(const std::string& name);
    virtual int myType () const override ;
    std::shared_ptr<File> addFile (const std::string& name, std::string checksum, long time);
    ~Directory(){};
};


#endif //CLIENT_DIRECTORY_H
