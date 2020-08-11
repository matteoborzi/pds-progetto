#ifndef CLIENT_JOBQUEUE_H
#define CLIENT_JOBQUEUE_H

#include <string>
#include <mutex>
#include <condition_variable>
#include <list>
#include "../../common/Action.h"
#include "Job.h"

/**
 * Thread-safe structure to manage Jobs
 */
class JobQueue {
    std::mutex m;
    std::condition_variable empty, full;
    std::list<Job> queue, sent;

public:
    void add(Job& j);

    Job getLastAndSetSent();

    void setConcluded(std::string& path);

    void retry(std::string& path);

};


#endif //CLIENT_JOBQUEUE_H
