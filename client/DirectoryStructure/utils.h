//
// Created by Angelica on 28/07/2020.
//

#ifndef CLIENT_HTILS_H
#define CLIENT_HTILS_H

#include <boost/algorithm/string.hpp>
#include "../../common/time_utils.h"
#include "../../common/messages/DirectoryEntryMessage.pb.h"
#include "Directory.h"
#include "File.h"


bool deleteDirectoryOrFile(std::string& path);
bool addDirectory(std::string& path);
bool addFile(std::string& path);
bool addFile(std::string& path, std::string& checksum, long time);
std::shared_ptr<Directory> getDirectory(std::string& path);
std::shared_ptr<File> getFile(std::string& path);
std::string getLast(std::string& path);

//TODO add method to getNotVisited starting from the root (with relative path)
//TODO add method to unclear visited flag for all element

Type toType(DirectoryEntryMessage::Type toConvert);
DirectoryEntryMessage::Type toDirectoryEntryMessage(Type toConvert);

#endif //CLIENT_HTILS_H
