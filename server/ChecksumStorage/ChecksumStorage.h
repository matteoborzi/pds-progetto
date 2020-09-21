//
// Created by rober on 21/09/2020.
//

#ifndef SERVER_CHECKSUMSTORAGE_H
#define SERVER_CHECKSUMSTORAGE_H

#define TMP_EXTENSION ".tmpbck"

std::optional<std::string> getChecksum(const std::string& path);

//in a transaction:
//delete all entry beginning with path
//delete folder (-r)
//commit
bool deleteFolderRecursively(const std::string& path);

//in a transaction:
//compute checksum
//insert into DB (PK as unique CONSTRAINT ON CONFLICT REPLACE)
//delete old file (if exists)
//rename temporary file
//commit
bool updateChecksum(const std::string& path);

#endif //SERVER_CHECKSUMSTORAGE_H
