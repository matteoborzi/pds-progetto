//
// Created by Angelica on 28/07/2020.
//

#include "utils.h"
#include "../Configuration/Configuration.h"
#include "../../common/Checksum.h"

std::shared_ptr<Directory> getParent(const std::string& path){
    std::shared_ptr<Directory> result = Directory::getRoot();
    std::vector<std::string> fields;
    boost::split(fields, path, boost::is_any_of("/"));

    //controllo che il formato del path sia corretto, ovvero /folder oppure ./folder
    if(fields[0] != "" && fields[0] != ".")
        return std::shared_ptr<Directory>(nullptr);

    //last corrisponde all'indice dell'ultimo elemento
    int last = fields.size()-1;

    //se l'ultimo elemento è vuoto, lo rimuovo dal vector
    // es. un path che termina con / ( folder1/folder2/ )
    if(fields[last] == "") {
        fields = std::vector(fields.begin(), fields.end() - 1);
        last--;
    }

    //corrisponde al caso in cui il path è / oppure ./ ( root ha come padre nullptr)
    if(last == 0)
        return std::shared_ptr<Directory>(nullptr);
    int index = 0;
    for(std::string field : fields){
        boost::algorithm::trim(field);
        if(field == "") {
            if (index == 0) {
                index++;
                continue;
            }else{
                //errore nel path es. /folder1//folder2
                result = std::shared_ptr<Directory>(nullptr);
                break;
            }
        }

        //sono all'ultimo elemento, non devo considerarlo perchè cerco il padre
        if(index == last)
            break;

        //l'iterazione precedente ha ritornato un nullptr
        if(result == nullptr)
            break;

        std::shared_ptr<DirectoryEntry> next = result->get(field);
        if(next == nullptr || next->myType() == FILETYPE) {
            result = std::shared_ptr<Directory>(nullptr);
            break;
        }
        result = std::static_pointer_cast<Directory>(next);
        index++;
    }

    return result;
}

bool deleteDirectoryOrFile(const std::string &path) {
    std::shared_ptr<Directory> parent = getParent(path);
    std::string toDelete = getLast(path);
    bool res = false;
    if(parent == nullptr || toDelete == "")
        return res;
    res = parent->deleteEntry(toDelete);
    return res;
}

bool addDirectory(const std::string& param_path){

    std::string path=param_path;
    //if the path doesn't start with "/", it is added
    if(path[0]!='/')
        path = "/" + param_path;

    std::shared_ptr<Directory> parent = getParent(path);
    std::string toAdd = getLast(path);
    bool res = false;
    if(parent == nullptr || toAdd == "")
        return res;
    std::shared_ptr<Directory> added = parent->addDirectory(toAdd);
    if(added != nullptr)
        res = true;
    return res;
}

bool addFile(const std::string& param_path){
    bool res = false;
    std::string checksum = "";
//    try{
//        checksum = computeChecksum(param_path);
//    }
//    catch(...){
//        //if something wrong in checksum computation
//        return res;
//    }
//    if(checksum == "")
//        return res;
    std::optional<Configuration> conf=Configuration::getConfiguration();
    if(!conf.has_value())
        throw std::runtime_error("Impossible to get configuration");
    std::string abs_path = conf.value().getPath();

    std::string path=param_path;
    //if the path doesn't start with "/", it is added
    if(path[0]!='/')
        path = "/" + param_path;
    std::filesystem::directory_entry file{abs_path+path};
    if(!file.exists() || !file.is_regular_file())
        return res;
    std::time_t time = last_edit_time(file);
    if(time < 0)
        return res;
    res = addFile(path, checksum, time);
    return res;
}

bool addFile(const std::string& path, std::string& checksum, long time){
    std::shared_ptr<Directory> parent = getParent(path);
    std::string toAdd = getLast(path);
    bool res = false;
    if(parent == nullptr || toAdd == "")
        return res;
    std::shared_ptr<File> added = parent->addFile(toAdd, checksum, time);
    if(added != nullptr)
        res = true;
    return res;
}

std::shared_ptr<Directory> getDirectory(const std::string& path){
    std::shared_ptr<Directory> parent = getParent(path);
    std::string toGet = getLast(path);
    std::shared_ptr<Directory> res = std::shared_ptr<Directory>(nullptr);
    std::shared_ptr<DirectoryEntry> child{};
    if(parent == nullptr || toGet == "")
        return res;
    child = parent->get(toGet);
    if(child != nullptr && child->myType() == DIRTYPE)
        res = std::static_pointer_cast<Directory>(child);
    return res;
}

std::shared_ptr<File> getFile(const std::string& path){
    std::shared_ptr<Directory> parent = getParent(path);
    std::string toGet = getLast(path);
    std::shared_ptr<File> res = std::shared_ptr<File>(nullptr);
    std::shared_ptr<DirectoryEntry> child{};
    if(parent == nullptr || toGet == "")
        return res;
    child = parent->get(toGet);
    if(child != nullptr && child->myType() == FILETYPE)
        res = std::static_pointer_cast<File>(child);
    return res;
}


/*
 * ritorno l'ultimo elemento valido
 * in caso di path che termina con uno / considero valido il campo precedente
 */
std::string getLast(const std::string& path){
    std::vector<std::string> fields{};
    boost::split(fields, path, boost::is_any_of("/"));
    std::string last = fields.back();
    if(last == "")
        last = fields[fields.size()-2];
    boost::algorithm::trim(last);
    return last;
}

BackupPB::DirectoryEntryMessage::Type toDirectoryEntryMessage(Type toConvert) {
    switch (toConvert) {
        case DIRTYPE:
            return BackupPB::DirectoryEntryMessage::Type::DirectoryEntryMessage_Type_DIRTYPE;
        case FILETYPE:
            return BackupPB::DirectoryEntryMessage::Type::DirectoryEntryMessage_Type_FILETYPE;
    }
    return BackupPB::DirectoryEntryMessage_Type_DIRTYPE;
}

Type toType(BackupPB::DirectoryEntryMessage::Type toConvert) {
    switch (toConvert) {
        case BackupPB::DirectoryEntryMessage::Type::DirectoryEntryMessage_Type_DIRTYPE:
            return DIRTYPE;
        case BackupPB::DirectoryEntryMessage::Type::DirectoryEntryMessage_Type_FILETYPE:
            return FILETYPE;
    }
    return DIRTYPE;
}

std::unordered_map<std::string, std::shared_ptr<DirectoryEntry>> getNotVisited() {
    return Directory::getRoot()->getNotVisited();
}

void unsetAllVisited() {
    Directory::getRoot()->unsetVisited();
}
