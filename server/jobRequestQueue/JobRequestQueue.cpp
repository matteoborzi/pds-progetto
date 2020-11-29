#include "JobRequestQueue.h"

/**
 * Insert a JobRequest into the shared queue
 * @param jr
 */
void JobRequestQueue::enqueueJobRequest(BackupPB::JobRequest& jr){
    std::unique_lock l{m};

    queue.push(jr);
    empty.notify_one();

}

/**
 * Read a JobRequest from the shared queue
 * @return JobRequest read
 */
BackupPB::JobRequest JobRequestQueue::dequeueJobRequest(){
    std::unique_lock l{m};

    BackupPB::JobRequest jr{};
    empty.wait(l, [this]()->bool { return !queue.empty(); });
    jr = queue.front();
    queue.pop();

    return jr;
}
