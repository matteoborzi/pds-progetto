#ifndef CLIENT_DIRECTORYENTRY_H
#define CLIENT_DIRECTORYENTRY_H

enum Type {DIRTYPE, FILETYPE};

#include <string>
#include <list>

/**
 * Virtual base class for Directory and file
 */
class DirectoryEntry {
private:
    std::string name;
    bool visited;
protected:
    DirectoryEntry(std::string name): name(name){
        visited = false;
    }
public:
    std::string getName() const {
        return name;
    }
    void setVisited(bool value = true){
        visited = value;
        return;
    };
    bool getVisited(){
        return visited;
    }
    virtual int myType () const = 0;

    virtual void unsetVisited(){
        visited=false;
    };

    ~DirectoryEntry(){};
};

#endif //CLIENT_DIRECTORYENTRY_H
