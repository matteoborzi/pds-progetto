#include <stdexcept>
#include "Job.h"

/**
 * trick to insert a Job in the JobQueue in case the program is terminating
 * and there is a thread waiting on the empty queue
 */
#define TERMINATION_ACTION CANCELLED
#define TERMINATION_PATH ""

const std::string &Job::getPath() const {
    return path;
}

Action Job::getAct() const {
    return act;
}

Job::Job(const std::string &path, Action act, bool isFile) : path(path), act(act), isFile(isFile) {
   validateAct(act);
}

bool Job::getIsFile() const {
    return isFile;
}

void Job::setAct(Action a) {
    validateAct(a);
    act=a;
}

/**
 * Redefinition of operator== and operator!=
 * @return true if the path are equal and are both files or both directories
 */
bool Job::operator==(Job const &j) const {
    return path==j.path && isFile==j.isFile;
}

bool Job::operator!=(Job const &j) const {
    return path!=j.path || isFile!=j.isFile;
}

/**
 * Performs a check on the coherency of the isFile flag and the Action
 * ( a file cannot have as Action ADD_DIRECTORY and a directory cannot have ADD_FILE )
 * @param the Action
 * @throws std::logic_error in case of incoherency
 */
void Job::validateAct(Action a){
    if((isFile && a == ADD_DIRECTORY) || (!isFile && a==ADD_FILE ))
        throw std::logic_error("Impossible to set such an action on this file");
}

bool Job::isTerminatation() {
    return path==TERMINATION_PATH && act==TERMINATION_ACTION ;
}

const Job Job::terminationJob() {
    return Job(TERMINATION_PATH, TERMINATION_ACTION, false);
}


