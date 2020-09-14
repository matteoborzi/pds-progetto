#include <iostream>
#include <boost/asio/ip/tcp.hpp>

int main() {
    boost::asio::io_service io_service;
//socket creation
    boost::asio::ip::tcp::socket socket(io_service);
//connection
    socket.connect( boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 8080 ));
    return 2;
}
