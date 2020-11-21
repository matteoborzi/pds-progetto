#ifndef CLIENT_CONNECTION_UTILS_H
#define CLIENT_CONNECTION_UTILS_H

#include <chrono>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/connect.hpp>

void custom_connect(boost::asio::ip::tcp::socket &socket,
                    boost::asio::ip::tcp::endpoint &endpoint,
                    std::chrono::steady_clock::duration timeout,
                    boost::asio::io_context& io_context);
void custom_handshake(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket_stream,
                      std::chrono::steady_clock::duration timeout,
                      boost::asio::io_context& io_context);

#endif //CLIENT_CONNECTION_UTILS_H
