#ifndef SOCKET_UTILS
#define SOCKET_UTILS

#include <boost/asio/ip/tcp.hpp>

template<class T>
T readFromSocket(boost::asio::ip::tcp::socket& s){
    size_t size;
    size_t ret;

    try{
        ret= s.receive(boost::asio::buffer(&size, sizeof(size)));
    }catch(boost::system::system_error& e) {
        //TODO retry?
        throw std::runtime_error("Something wrong happened");
    }
    if(ret<=0){
        //TODO can get here?
        throw std::runtime_error("Something wrong happened");
    }
    if(size<=0)
        //TODO decide what is better to do
        return T{};
    char values[size];
    try {
        ret = s.receive(boost::asio::buffer(values, size));
    }catch(boost::system::system_error& e) {
        //TODO retry?
        throw std::runtime_error("Something wrong happened");
    }
    if(ret<=0){
        //TODO can get here?
        throw std::runtime_error("Something wrong happened");
    }
    T result;
    result.ParseFromArray(values, size);
    return result;
};

template<class T>
bool writeToSocket(boost::asio::ip::tcp::socket& s,T message){
    size_t size = message.ByteSizeLong();
    size_t ret;
    try{
        ret= s.send(boost::asio::buffer(&size, sizeof(size)));
    }catch(boost::system::system_error& e) {
        //TODO retry?
        throw std::runtime_error("Something wrong happened");
    }
    if(ret!=sizeof(size))
        //TODO can get here?
        return false;
    char serializedMessage[size];
    message.SerializeToArray(serializedMessage, size);
    try {
        ret = s.send(boost::asio::buffer(serializedMessage, size));
    }catch(boost::system::system_error& e) {
        //TODO retry?
        throw std::runtime_error("Something wrong happened");
    }
    if(ret!=size)
        //TODO can get here?
        return false;

    return true;
}

#endif