#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "log_utils.h"

// Get the current timestamp and convert into string
std::string get_timestamp(){
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto ts = std::string(ctime(&t));

    ts.erase(std::remove(ts.begin(), ts.end(), '\n'), ts.end());
    return ts;
}

// Print message for logged users
void print_log_message(const std::string& ip, const std::string& user, const std::string& logmsg) {
    std::stringstream buffer;
    buffer << "[" << get_timestamp() << ", " << ip << ", " << user << "]: " << logmsg << "\n";
    std::cout << buffer.str();
}

// Print message for a specific connection
void print_log_message(const std::string& ip, const std::string& logmsg) {
    std::stringstream buffer;
    buffer  <<"["<< get_timestamp() << ", "<< ip << "]: "<<  logmsg << "\n";
    std::cout << buffer.str();
}

// Print error for a specific connection
void print_log_error(const std::string& ip, const std::string& logerr) {
    std::stringstream buffer;
    buffer << "[" << get_timestamp() << ", "<< ip << "]: "<<  logerr << "\n";
    std::cerr << buffer.str();
}

void print_log_error(const std::string& ip, const std::string& user, const std::string& logmsg) {
    std::cout << "[" << get_timestamp() << ", " << ip << ", " << user << "]: " << logmsg << std::endl;
}

