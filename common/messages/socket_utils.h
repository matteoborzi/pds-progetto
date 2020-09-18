#ifndef SOCKET_UTILS
#define SOCKET_UTILS

#include <boost/asio/ip/tcp.hpp>

template<class T>
T readFromSocket(boost::asio::ip::tcp::socket& s){
    size_t size;
    size_t ret = s.receive(boost::asio::buffer(&size, sizeof(size)));
    if(ret<=0)
        //TODO search for better error detection and messages
        throw std::runtime_error("Something wrong happened");
    if(size<=0)
        //TODO decide what is better to do
        return T{};
    char values[size];
    ret = s.receive(boost::asio::buffer(values, size));
    if(ret<=0)
        //TODO search for better error detection and messages
        throw std::runtime_error("Something wrong happened");
    T result;
    result.ParseFromArray(values, size);
    return result;
};

template<class T>
bool writeToSocket(boost::asio::ip::tcp::socket& s,T message){
    size_t size = message.ByteSizeLong();
    size_t ret = s.send(boost::asio::buffer(&size, sizeof(size)));
    if(ret<=0)
        //TODO search for better error detection and messages
        return false;
    char serializedMessage[size];
    message.SerializeToArray(serializedMessage, size);

    ret = s.send(boost::asio::buffer(serializedMessage, size));

    if(ret!=size)
        //TODO search for better error detection and messages
        return false;

    return true;
}

#endif