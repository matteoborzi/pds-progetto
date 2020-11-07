//
// Created by rober on 11/08/2020.
//

#ifndef CLIENT_WATCHER_H
#define CLIENT_WATCHER_H

#include <atomic>
#include "../job/JobQueue.h"

void watch(JobQueue &queue, std::atomic_bool&);

#endif //CLIENT_WATCHER_H
