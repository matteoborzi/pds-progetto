#ifndef CLIENT_INITIALIZATION_H
#define CLIENT_INITIALIZATION_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <string>

bool login(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&, std::string &, std::string &);
bool chooseWorkspace(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&, std::string &, std::string &);

#endif //CLIENT_INITIALIZATION_H
