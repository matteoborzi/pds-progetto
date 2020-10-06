//
// Created by rober on 06/10/2020.
//

#ifndef CLIENT_RESTORE_H
#define CLIENT_RESTORE_H

#include <boost/asio/ip/tcp.hpp>
#include <string>

bool restore(boost::asio::ip::tcp::socket &socket, std::string &machineId, std::string &path);


#endif //CLIENT_RESTORE_H
