#ifndef SERVER_LOAD_H
#define SERVER_LOAD_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <string>
#include <memory>
#include "../pathPool/PathPool.h"

std::shared_ptr<PathPool> loadWorkspace(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&, std::string&);

#endif //SERVER_LOAD_H
