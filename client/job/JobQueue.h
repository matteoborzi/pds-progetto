#ifndef CLIENT_JOBQUEUE_H
#define CLIENT_JOBQUEUE_H

#include <string>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <queue>
#include "../../common/Action.h"
#include "Job.h"

class JobQueue {
    std::mutex m;
    std::condition_variable empty, full;
    std::unordered_map<std::string,Action> to_send, sent;
    std::queue<std::string> queue;

public:
    void add(std::string path, Action act);

    Job getLastAndSetSent();

    void setConcluded(std::string& path);

    void retry(std::string& path);

};


#endif //CLIENT_JOBQUEUE_H
