//
// Created by rober on 15/09/2020.
//

#include "Waiter.h"
#include <iostream>

std::atomic_int Waiter::counter=0;
std::mutex Waiter::m{};
std::condition_variable Waiter::waitAvailable{};

Waiter::Waiter() {
    std::unique_lock l(m);
    waitAvailable.wait(l, []()->bool{return counter<=MAX_CONCURRENT_CLIENTS;});
    counter++;
}

Waiter::~Waiter() {
    counter--;
    waitAvailable.notify_one();
    std::cout<<counter<<" threads active"<<std::endl;
}


