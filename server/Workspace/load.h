//
// Created by rober on 06/10/2020.
//

#ifndef SERVER_LOAD_H
#define SERVER_LOAD_H

#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <memory>
#include "../pathPool/PathPool.h"

std::shared_ptr<PathPool> loadWorkspace(boost::asio::ip::tcp::socket&, std::string&);

#endif //SERVER_LOAD_H
