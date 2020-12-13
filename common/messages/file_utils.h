#ifndef FILE_UTILS_COMMON_H
#define FILE_UTILS_COMMON_H

#include <boost/asio/ip/tcp.hpp>
#include <string>

void sendFile(boost::asio::ip::tcp::socket&, const std::string&, size_t);
void receiveFile(boost::asio::ip::tcp::socket&, const std::string&, size_t);

#endif //FILE_UTILS_COMMON_H
