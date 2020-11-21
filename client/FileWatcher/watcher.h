#ifndef CLIENT_WATCHER_H
#define CLIENT_WATCHER_H

#include <atomic>
#include "../job/JobQueue.h"

void watch(JobQueue &queue, std::atomic_bool&);

#endif //CLIENT_WATCHER_H
