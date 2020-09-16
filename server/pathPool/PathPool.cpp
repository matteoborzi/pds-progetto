//
// Created by rober on 15/09/2020.
//

#include "PathPool.h"

std::unordered_set<std::string> PathPool::pool{};
std::mutex PathPool::m{};

PathPool::PathPool(std::string &path) {
    std::unique_lock l(m);

    this->path = std::nullopt;

    //search for presence in pool

    //set local field if not present and insert in pool

}

PathPool::~PathPool() {
    std::unique_lock l(m);

    //check if path has value

    //throws exception if not present in pool

    //delete from pool

}

std::string PathPool::getPath() {
    return path.value();
}

bool PathPool::isValid() {
    return path.has_value();
}




