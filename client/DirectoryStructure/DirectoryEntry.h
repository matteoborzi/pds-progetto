//
// Created by Angelica on 24/07/2020.
//

#ifndef CLIENT_DIRECTORYENTRY_H
#define CLIENT_DIRECTORYENTRY_H

enum Type {DIRTYPE, FILETYPE};

#include <string>
#include <list>

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
    void unsetVisited(){
        visited=false;
    };
    ~DirectoryEntry(){};
};

/*
 * TODO
 * aggiungere un campo bool per settare se la entry è settata
 * come da cancellare oppure no,
 * per evitare di accedere ai campi di un oggetto
 * che a momenti verrà cancellato*/

#endif //CLIENT_DIRECTORYENTRY_H
