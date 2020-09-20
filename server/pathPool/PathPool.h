//
// Created by rober on 15/09/2020.
//

#ifndef SERVER_PATHPOOL_H
#define SERVER_PATHPOOL_H


#include <string>
#include <unordered_set>
#include <mutex>
#include <memory>

class PathPool {
    std::optional<std::string> path;


    static std::unordered_set<std::string> pool;
    static std::mutex m;

public:
    PathPool(const std::string& path);
    ~PathPool();

    std::string getPath();
    bool isValid();


};


#endif //SERVER_PATHPOOL_H
