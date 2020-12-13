#ifndef CLIENT_RESTORE_H
#define CLIENT_RESTORE_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <string>

bool restore(boost::asio::ip::tcp::socket& socket, std::string &machineId, std::string &path);


#endif //CLIENT_RESTORE_H
