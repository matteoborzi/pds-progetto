//
// Created by rober on 06/10/2020.
//

#ifndef CLIENT_INITIALIZATION_H
#define CLIENT_INITIALIZATION_H

#include <boost/asio/ip/tcp.hpp>
#include <string>

bool login(boost::asio::ip::tcp::socket &, std::string &, std::string &);
bool chooseWorkspace(boost::asio::ip::tcp::socket &, std::string &, std::string &);

#endif //CLIENT_INITIALIZATION_H
