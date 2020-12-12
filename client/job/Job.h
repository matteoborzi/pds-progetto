#ifndef SERVER_JOB_H
#define SERVER_JOB_H

#include <string>
#include "../../common/Action.h"

class Job {
    std::string path;
    Action act;
    bool isFile;
    
    void validateAct(Action a);

public:
    Job(const std::string &path, Action act, bool isFile);
    const std::string& getPath() const;
    Action getAct() const;
    void setAct(Action a);
    bool getIsFile() const;
    bool operator==(Job const& j) const;
    bool operator!=(Job const& j) const;

    bool isTermination();

    static const Job terminationJob();
};


#endif //SERVER_JOB_H
