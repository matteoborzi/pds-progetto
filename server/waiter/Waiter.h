//
// Created by rober on 15/09/2020.
//

#ifndef SERVER_WAITER_H
#define SERVER_WAITER_H
#include <atomic>
#include <condition_variable>

#define MAX_CONCURRENT_CLIENTS 10

class Waiter {

    static std::atomic_int counter;
    static std::condition_variable waitAvailable;
    static std::mutex m;

public:
    Waiter();
    ~Waiter();

};




#endif //SERVER_WAITER_H
