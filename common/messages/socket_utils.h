#ifndef SOCKET_UTILS
#define SOCKET_UTILS

#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/ip/tcp.hpp>


#define MAX_MESSAGE_SIZE 1 * 1024 * 1024 * 1024 //1 GB max PB message dimension

template<class T>
/**
 * function to read a message from socket
 * @tparam T type of message to read
 * @param socket from which read data
 * @return message
 */
T readFromSocket(boost::asio::ip::tcp::socket& s){
    size_t size;
    size_t ret;
    try{
        //reading dimension of the message
        ret=  boost::asio::read(s,boost::asio::buffer(&size, sizeof(size)));
    }catch(boost::system::system_error& e) {
        throw std::runtime_error("Socket has been closed, cannot read message size");
    }
    if(ret<=0 || size<=0 ){
        throw std::runtime_error("Unexpected message size read from socket");
    }
    if(size> MAX_MESSAGE_SIZE )
        throw std::runtime_error("Received anormal message size, aborting");

    //allocating bytes for the message
    char values[size+1];
    try {
        //reading the message from socket
        ret = boost::asio::read(s,boost::asio::buffer(values, size));
        //terminating the stream of bytes
        values[size]='\0';
    }catch(boost::system::system_error& e) {
        throw std::runtime_error("Socket has been closed, cannot read message");
    }
    if(ret<=0){
        throw std::runtime_error("Unexpected message read from socket");
    }
    //deserializing result
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
 */
void writeToSocket(boost::asio::ip::tcp::socket& s, T message){
    size_t size = message.ByteSizeLong();
    size_t ret;

    if(!message.IsInitialized())
        throw std::logic_error("Message to send is not initialized");

    try{
       //writing dimension of the file on the socket
       ret= boost::asio::write(s,boost::asio::buffer(&size, sizeof(size)));
    }catch(boost::system::system_error& e) {
        throw std::runtime_error("Socket has been closed, cannot write message size");
    }
    if(ret!=sizeof(size))
        throw std::runtime_error("Unexpected number of bytes written on socket");

    //getting serialized message
    char serializedMessage[size+1];
    message.SerializeToArray(serializedMessage, size);
    serializedMessage[size]='\0';
    try {
        //writing message on the socket
        ret = boost::asio::write(s,boost::asio::buffer(serializedMessage, size));
    }catch(boost::system::system_error& e) {
        throw std::runtime_error("Socket has been closed, cannot write message");
    }
    if(ret!=size)
        throw std::runtime_error("Unexpected number of bytes written on socket for message");

}

void close_socket(boost::asio::ip::tcp::socket& socket);

#endif