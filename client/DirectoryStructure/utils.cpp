#include "utils.h"
#include "../Configuration/Configuration.h"
#include "../../common/Checksum.h"

std::shared_ptr<Directory> getParent(const std::string& path);

/**
 * Function to get the name of the parent of an element with given path
 * @param path
 * @return the parent element
 */
std::shared_ptr<Directory> getParent(const std::string& path){
    std::shared_ptr<Directory> result = Directory::getRoot();
    std::vector<std::string> fields;
    boost::split(fields, path, boost::is_any_of("/"));

    //checking the correct format ot the path (/folder or ./folder)
    if(fields[0] != "" && fields[0] != ".")
        return std::shared_ptr<Directory>(nullptr);

    //last will represent the index ot the last element
    int last = fields.size()-1;

    //removing last (empty) element for paths terminating with /
    if(fields[last] == "") {
        fields = std::vector(fields.begin(), fields.end() - 1);
        last--;
    }

    //case where path is / or ./
    if(last == 0)
        return std::shared_ptr<Directory>(nullptr);
    int index = 0;
    for(std::string field : fields){
        boost::algorithm::trim(field);
        if(field == "") {
            if (index == 0) {
                //skipping first empty field
                index++;
                continue;
            }else{
                //wrong path format (ex: /folder1//folder2)
                result = std::shared_ptr<Directory>(nullptr);
                break;
            }
        }

        //get to the last element
        if(index == last)
            //terminating the search
            break;

        //getting a non existing directory from previous loop iteration
        if(result == nullptr)
            break;

        std::shared_ptr<DirectoryEntry> next = result->get(field);
        if(next == nullptr || next->myType() == FILETYPE) {
            //the desired folder does not exists or it is a file
            result = std::shared_ptr<Directory>(nullptr);
            break;
        }

        //updating the result
        result = std::static_pointer_cast<Directory>(next);
        index++;
    }

    return result;
}

/**
 * Delete an element given its path
 * @param path of the element
 * @return tru on success
 */
bool deleteDirectoryOrFile(const std::string &path) {
    //getting parent of the element
    std::shared_ptr<Directory> parent = getParent(path);

    //getting name of the element
    std::string toDelete = getLast(path);
    bool res = false;

    //parent do not exists
    if(parent == nullptr || toDelete == "")
        return res;

    //deleting from parent
    res = parent->deleteEntry(toDelete);
    return res;
}


/**
 * Create a directory with a given name
 * @param param_path
 * @return true on success
 */
bool addDirectory(const std::string& param_path){

    std::string path=param_path;
    //if the path doesn't start with "/", it is added
    if(path[0]!='/')
        path = "/" + param_path;

    //getting parent and name of the element
    std::shared_ptr<Directory> parent = getParent(path);
    std::string toAdd = getLast(path);
    bool res = false;

    //parent not found or name not valid
    if(parent == nullptr || toAdd == "")
        return res;

    //adding the directory to the parent
    std::shared_ptr<Directory> added = parent->addDirectory(toAdd);
    if(added != nullptr)
        res = true;
    return res;
}

/**
 * Create a directory with a given name loading information about size and date from the file system
 * @param param_path
 * @return true on success
 */
bool addFile(const std::string& param_path){
    bool res = false;

    //getting configuration
    std::optional<Configuration> conf=Configuration::getConfiguration();
    if(!conf.has_value())
        throw std::runtime_error("Impossible to get configuration");
    std::string abs_path = conf.value().getPath();

    std::string path=param_path;
    //if the path doesn't start with "/", it is added
    if(path[0]!='/')
        path = "/" + param_path;

    //getting element from filesystem
    std::filesystem::directory_entry file{abs_path+path};
    if(!file.exists() || !file.is_regular_file())
        return res;
    std::time_t time = last_edit_time(file);
    if(time < 0)
        return res;
    res = addFile(path, "", time, file.file_size());
    return res;
}

/**
 * Add a file given its specifics
 * @param path
 * @param checksum
 * @param time
 * @param size
 * @return true on success
 */
bool addFile(const std::string& path, const std::string& checksum, long time, size_t size){

    //getting parent's and own name
    std::shared_ptr<Directory> parent = getParent(path);
    std::string toAdd = getLast(path);
    bool res = false;
    if(parent == nullptr || toAdd == "")
        return res;

    //adding file to the parent
    std::shared_ptr<File> added = parent->addFile(toAdd, checksum, time, size);
    if(added != nullptr)
        res = true;
    return res;
}

/**
 * Retrieve a directory given the path
 * @param path
 * @return the pointer or nullptr
 */
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

/**
 * Retrieve a file given the path
 * @param path
 * @return the pointer or nullptr
 */
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


/**
 * Function to get relative name for a path (in case of path terminating with / the previous part is considered)
 * @param path
 * @return the relative name
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

/**
 * Utility to convert Type to DirectoryEntry::Type enum
 * @param toConvert
 * @return corresponding DirectoryEntryMessage::Type
 */
BackupPB::DirectoryEntryMessage::Type toDirectoryEntryMessage(Type toConvert) {
    switch (toConvert) {
        case DIRTYPE:
            return BackupPB::DirectoryEntryMessage::Type::DirectoryEntryMessage_Type_DIRTYPE;
        case FILETYPE:
            return BackupPB::DirectoryEntryMessage::Type::DirectoryEntryMessage_Type_FILETYPE;
    }
    return BackupPB::DirectoryEntryMessage_Type_DIRTYPE;
}


/**
 * Utility to convert DirectoryEntry::Type to Type enum
 * @param toConvert
 * @return corresponding Type
 */
Type toType(BackupPB::DirectoryEntryMessage::Type toConvert) {
    switch (toConvert) {
        case BackupPB::DirectoryEntryMessage::Type::DirectoryEntryMessage_Type_DIRTYPE:
            return DIRTYPE;
        case BackupPB::DirectoryEntryMessage::Type::DirectoryEntryMessage_Type_FILETYPE:
            return FILETYPE;
    }
    return DIRTYPE;
}

/**
 * Get the list of all elements not visited during scan
 * @return map<path, pointer>
 */
std::unordered_map<std::string, std::shared_ptr<DirectoryEntry>> getNotVisited() {
    return Directory::getRoot()->getNotVisited();
}

/**
 * Clears all visited flag of all elements
 */
void unsetAllVisited() {
    Directory::getRoot()->unsetVisited();
}
