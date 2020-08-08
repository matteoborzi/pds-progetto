#include "Job.h"

const std::string &Job::getPath() const {
    return path;
}

Action Job::getAct() const {
    return act;
}

Job::Job(const std::string &path, Action act, bool isFile) : path(path), act(act), isFile(isFile) {}

bool Job::getIsFile() const {
    return isFile;
}

void Job::setAct(Action a) {
    act=a;
}

bool Job::operator==(Job const &j) const {
    return path==j.path && isFile==j.isFile;
}


bool Job::operator!=(Job const &j) const {
    return path!=j.path || isFile!=j.isFile;
}

