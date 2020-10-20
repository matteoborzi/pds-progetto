#include <chrono>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "log_utils.h"

void print_log_message(const std::string& ip, const std::string& user, const std::string& text) {
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto timestamp = std::string(ctime(&t));

    timestamp.erase(std::remove(timestamp.begin(), timestamp.end(), '\n'), timestamp.end());

    std::cout<<"["<< timestamp  << ", "<< ip << ", " << user <<"]: "<<text<<std::endl;

}