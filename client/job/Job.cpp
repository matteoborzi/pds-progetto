#include "Job.h"

const std::string &Job::getPath() const {
    return path;
}

Action Job::getAct() const {
    return act;
}

Job::Job(const std::string &path, Action act) : path(path), act(act) {}
