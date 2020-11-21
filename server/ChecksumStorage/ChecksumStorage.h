#ifndef SERVER_CHECKSUMSTORAGE_H
#define SERVER_CHECKSUMSTORAGE_H

#include <string>
#include <optional>

#define TMP_EXTENSION ".tmpbck"

std::optional<std::string> getChecksum(const std::string& path);
bool deleteFolderRecursively(const std::string& path);
bool updateChecksum(const std::string& path);

#endif //SERVER_CHECKSUMSTORAGE_H
