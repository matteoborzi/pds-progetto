#include "JobRequestQueue.h"

void JobRequestQueue::enqueueJobRequest(BackupPB::JobRequest& jr){
    std::unique_lock l{m};

    queue.push(jr);
    empty.notify_one();

}

BackupPB::JobRequest JobRequestQueue::dequeueJobRequest(){
    std::unique_lock l{m};

    BackupPB::JobRequest jr{};
    empty.wait(l, [this]()->bool { return !queue.empty(); });
    jr = queue.front();
    queue.pop();

    return jr;
}
