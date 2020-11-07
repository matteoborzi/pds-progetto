#ifndef SERVER_LOG_UTILS_H
#define SERVER_LOG_UTILS_H

#include <string>

void print_log_message(const std::string&, const std::string&);
void print_log_message(const std::string&, const std::string&, const std::string&);
void print_log_error(const std::string&, const std::string&);
void print_log_error(const std::string&, const std::string&, const std::string&);

#endif //SERVER_LOG_UTILS_H
