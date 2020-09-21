//
// Created by rober on 15/09/2020.
//

#include "PathPool.h"

std::unordered_set<std::string> PathPool::pool{};
std::mutex PathPool::m{};

PathPool::PathPool(const std::string &path, bool restore) {
    std::unique_lock l(m);

    this->path = std::nullopt;
    this->restore = restore;
    //search for presence in pool
    if(pool.find(path)==pool.end()) {
        //set local field if not present and insert in pool
        pool.insert(path);
        this->path=path;
    }

}

PathPool::~PathPool() {
    std::unique_lock l(m);

    //check if path has value
    if(path.has_value()) {
        //TODO destructor should be noexcept
        //throws exception if not present in pool
        if(pool.find(path.value())==pool.end())
            throw std::runtime_error("Error while trying to remove "+path.value()+" from pathPool, since not present");
        //delete from pool
        pool.erase(path.value());
    }

}

std::string PathPool::getPath() {
    return path.value();
}

bool PathPool::isValid() {
    return path.has_value();
}

bool PathPool::getRestore(){
    return restore;
}




