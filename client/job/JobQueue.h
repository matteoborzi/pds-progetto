#ifndef CLIENT_JOBQUEUE_H
#define CLIENT_JOBQUEUE_H

#include <string>
#include <mutex>
#include <condition_variable>
#include <list>

#include "Job.h"

#include "../../common/Action.h"


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

    void setConcluded(const std::string& path);

    void retry(const std::string& path);

    void addIfEmpty(const Job &job);

    void wakeAll();
};


#endif //CLIENT_JOBQUEUE_H
