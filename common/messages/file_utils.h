#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <boost/asio/ip/tcp.hpp>
#include <string>

void sendFile(boost::asio::ip::tcp::socket &,const std::string&);
void receiveFile(boost::asio::ip::tcp::socket &,const std::string&);

#endif //SERVER_JOB_UTILS_H
