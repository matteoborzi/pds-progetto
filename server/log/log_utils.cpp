#include <chrono>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "log_utils.h"

//TODO rendere atomiche le operazioni
// Concatenazione atomica di stringhe
// \n inserito nella stringa
// stampa atomica + flush

std::string get_timestamp(){
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto ts = std::string(ctime(&t));

    ts.erase(std::remove(ts.begin(), ts.end(), '\n'), ts.end());
    return ts;
}

void print_log_message(const std::string& ip, const std::string& user, const std::string& logmsg) {
    std::cout << "[" << get_timestamp() << ", " << ip << ", " << user << "]: " << logmsg << std::endl;
}

void print_log_message(const std::string& ip, const std::string& logmsg) {
    std::cout <<"["<< get_timestamp() << ", "<< ip << "]: "<<  logmsg << std::endl;
}

void print_log_error(const std::string& ip, const std::string& logerr) {
    std::cerr << "[" << get_timestamp() << ", "<< ip << "]: "<<  logerr << std::endl;
}

void print_log_error(const std::string& ip, const std::string& user, const std::string& logmsg) {
    std::cout << "[" << get_timestamp() << ", " << ip << ", " << user << "]: " << logmsg << std::endl;
}

