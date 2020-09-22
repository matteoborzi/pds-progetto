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


bool deleteDirectoryOrFile(const std::string& path);
bool addDirectory(const std::string& path);
bool addFile(const std::string& path);
bool addFile(const std::string& path, std::string& checksum, long time);
std::shared_ptr<Directory> getDirectory(const std::string& path);
std::shared_ptr<File> getFile(const std::string& path);
std::string getLast(const std::string& path);

//TODO add method to getNotVisited starting from the root (with relative path)
//TODO add method to unclear visited flag for all element

Type toType(BackupPB::DirectoryEntryMessage::Type toConvert);
BackupPB::DirectoryEntryMessage::Type toDirectoryEntryMessage(Type toConvert);

#endif //CLIENT_HTILS_H
