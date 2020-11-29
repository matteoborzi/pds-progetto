#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "log_utils.h"

/**
 * Get the current timestamp and convert into string
 * @return timestamp string of current time
 */
std::string get_timestamp(){
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto ts = std::string(ctime(&t));

    ts.erase(std::remove(ts.begin(), ts.end(), '\n'), ts.end());
    return ts;
}

/**
 * Print a log message for a specific connection (no user is specified)
 * @param ip
 * @param logmsg content of the log
 */
void print_log_message(const std::string& ip, const std::string& logmsg) {
    std::stringstream buffer;
    buffer  <<"["<< get_timestamp() << ", "<< ip << "]: "<<  logmsg << "\n";
    std::cout << buffer.str();
}

/**
 * Print a log message for a logged user on a specific connection
 * @param ip
 * @param user
 * @param logmsg content of the log
 */
void print_log_message(const std::string& ip, const std::string& user, const std::string& logmsg) {
    std::stringstream buffer;
    buffer << "[" << get_timestamp() << ", " << ip << ", " << user << "]: " << logmsg << "\n";
    std::cout << buffer.str();
}

/**
 * Print an error message for a specific connection (no user is specified)
 * @param ip
 * @param logerr
 */
void print_log_error(const std::string& ip, const std::string& logerr) {
    std::stringstream buffer;
    buffer << "[" << get_timestamp() << ", "<< ip << "]: "<<  logerr << "\n";
    std::cerr << buffer.str();
}

/**
 * Print an error message for a logged user on a specific connection
 * @param ip
 * @param user
 * @param logmsg
 */
void print_log_error(const std::string& ip, const std::string& user, const std::string& logerr) {
    std::stringstream buffer;
    buffer << "[" << get_timestamp() << ", " << ip << ", " << user << "]: " << logerr << "\n";
    std::cerr << buffer.str();
}

