#ifndef SERVER_PATHPOOL_H
#define SERVER_PATHPOOL_H


#include <string>
#include <unordered_set>
#include <mutex>
#include <memory>

class PathPool {
    std::optional<std::string> path;
    bool restore;


    static std::unordered_set<std::string> pool;
    static std::mutex m;

public:
    PathPool(const std::string& path, bool restore);
    ~PathPool();

    std::string getPath();
    bool isValid();
    bool getRestore();
};


#endif //SERVER_PATHPOOL_H
