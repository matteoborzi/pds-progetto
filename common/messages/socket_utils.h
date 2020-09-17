#ifndef SOCKET_UTILS
#define SOCKET_UTILS

#include <boost/asio/ip/tcp.hpp>

template<class T>
T readFromSocket(boost::asio::ip::tcp::socket& s){

    return T{};
};

template<class T>
bool writeToSocket(boost::asio::ip::tcp::socket& s,T message){
    return false;
}

#endif