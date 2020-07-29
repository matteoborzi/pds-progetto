//
// Created by Angelica on 28/07/2020.
//

#include "utils.h"

std::shared_ptr<Directory> getParent(std::string& path){
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

    //corrisponde al caso in cui il pat è / oppure ./ ( root ha come padre nullptr)
    if(last == 0)
        return std::shared_ptr<Directory>(nullptr);
    int index = 0;
    for(std::string field : fields){
        if(field == "") {
            if (index == 0)
                continue;
            else{
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
        if(next == std::shared_ptr<Directory>(nullptr) || next->myType() == FILETYPE) {
            result = std::shared_ptr<Directory>(nullptr);
            break;
        }
        result = std::static_pointer_cast<Directory>(next);

        index++;
    }
    
    return result;
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
    for(std::string s : fields)
        std::cout << "-->" << s << std::endl;
    return fields.back();
}