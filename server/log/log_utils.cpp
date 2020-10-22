#include <chrono>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "log_utils.h"

std::string get_timestamp(){
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto ts = std::string(ctime(&t));

    ts.erase(std::remove(ts.begin(), ts.end(), '\n'), ts.end());
    return ts;
}

void print_log_message(const std::string& ip, const std::string& user, const std::string& logmsg) {
    std::cout << "[" << get_timestamp() << ", " << ip << ", " << user << "]: " << logmsg << std::endl;
}

void print_log_message(const std::string & ip, const std::string & logmsg) {
    std::cout<<"["<< get_timestamp() << ", "<< ip << "]: "<<  logmsg << std::endl;
}
