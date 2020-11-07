#ifndef FILE_UTILS_COMMON_H
#define FILE_UTILS_COMMON_H
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <string>

void sendFile(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&, const std::string&, size_t);
void receiveFile(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&, const std::string&, size_t);

#endif //FILE_UTILS_COMMON_H
