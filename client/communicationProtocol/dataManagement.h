//
// Created by rober on 06/10/2020.
//

#ifndef CLIENT_DATAMANAGEMENT_H
#define CLIENT_DATAMANAGEMENT_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include "../job/JobQueue.h"

void sendData(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&, JobQueue &, std::atomic_bool &);
void receiveData(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&, JobQueue &, std::atomic_bool &);

#endif //CLIENT_DATAMANAGEMENT_H
