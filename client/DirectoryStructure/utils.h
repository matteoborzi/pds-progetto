#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

#include "Directory.h"
#include "File.h"

#include <boost/algorithm/string.hpp>

#include "../../common/time_utils.h"
#include "../../common/messages/DirectoryEntryMessage.pb.h"



bool deleteDirectoryOrFile(const std::string& path);
bool addDirectory(const std::string& path);
bool addFile(const std::string& path);
bool addFile(const std::string& path, const std::string& checksum, long time, size_t size);
std::shared_ptr<Directory> getDirectory(const std::string& path);
std::shared_ptr<File> getFile(const std::string& path);
std::string getLast(const std::string& path);

std::unordered_map<std::string, std::shared_ptr<DirectoryEntry>> getNotVisited();
void unsetAllVisited();

Type toType(BackupPB::DirectoryEntryMessage::Type toConvert);
BackupPB::DirectoryEntryMessage::Type toDirectoryEntryMessage(Type toConvert);

#endif //CLIENT_UTILS_H
