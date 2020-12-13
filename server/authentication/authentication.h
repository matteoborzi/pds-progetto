#ifndef SERVER_AUTHENTICATION_H
#define SERVER_AUTHENTICATION_H

#include <string>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>

std::optional<std::string> doAuthentication(boost::asio::ip::tcp::socket&);


#endif //SERVER_AUTHENTICATION_H
