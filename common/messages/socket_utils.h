#ifndef SOCKET_UTILS
#define SOCKET_UTILS

#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/ssl.hpp>

template<class T>
/**
 * function to read a message from socket
 * @tparam T type of message to read
 * @param socket from which read data
 * @return message
 */
T readFromSocket(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& s){
    size_t size;
    size_t ret;
    try{
        ret=  boost::asio::read(s,boost::asio::buffer(&size, sizeof(size)));
    }catch(boost::system::system_error& e) {
        throw std::runtime_error("Socket has been closed, cannot read message size");
    }
    if(ret<=0 || size<=0){
        //TODO can get here?
        throw std::runtime_error("Something wrong happened HERE");
    }


    char values[size+1];
    try {
        ret = boost::asio::read(s,boost::asio::buffer(values, size));
        values[size]='\0';
    }catch(boost::system::system_error& e) {
        //TODO retry?
        throw std::runtime_error("Socket has been closed, cannot read message");
    }
    if(ret<=0){
        //TODO can get here?
        throw std::runtime_error("Something wrong happened");
    }
    T result;
    result.ParseFromArray(values, size);
    if(!result.IsInitialized())
        throw std::logic_error("A message that is not initialized has been received");
    return result;
};

template<class T>
/**
 * function to send a message on the socket
 * @tparam T type of message to send
 * @param socket on which send data
 * @param message to be sent
 * @return bool indicating success
 */
bool writeToSocket(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& s, T message){
    size_t size = message.ByteSizeLong();
    size_t ret;

    if(!message.IsInitialized())
        throw std::logic_error("Message to send is not initialized");

    try{
       ret= boost::asio::write(s,boost::asio::buffer(&size, sizeof(size)));
    }catch(boost::system::system_error& e) {
        //TODO retry?
        throw std::runtime_error("Socket has been closed, cannot write message size");
    }
    if(ret!=sizeof(size))
        //TODO can get here?
        return false;
    char serializedMessage[size+1];
    message.SerializeToArray(serializedMessage, size);
    serializedMessage[size]='\0';
    try {
        ret = boost::asio::write(s,boost::asio::buffer(serializedMessage, size));
    }catch(boost::system::system_error& e) {
        throw std::runtime_error("Socket has been closed, cannot write message");
    }
    if(ret!=size)
        //TODO can get here?
        return false;

    return true;
}

#endif