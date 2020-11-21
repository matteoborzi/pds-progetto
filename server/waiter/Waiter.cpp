#include "Waiter.h"

std::atomic_int Waiter::counter=0;
std::mutex Waiter::m{};
std::condition_variable Waiter::waitAvailable{};

Waiter::Waiter() {
    std::unique_lock l(m);
    waitAvailable.wait(l, []()->bool{return counter<MAX_CONCURRENT_CLIENTS;});
    counter++;
}

Waiter::~Waiter() {
    counter--;
    waitAvailable.notify_one();
}


