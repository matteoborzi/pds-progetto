#ifndef SERVER_JOB_H
#define SERVER_JOB_H

#include <string>
#include "../../common/Action.h"

class Job {
    std::string path;
    Action act;
public:
    Job(const std::string &path, Action act);
    const std::string& getPath() const;
    Action getAct() const;
};


#endif //SERVER_JOB_H
