//
// Created by rober on 06/10/2020.
//

#ifndef SERVER_JOBMANAGER_H
#define SERVER_JOBMANAGER_H

#include <boost/asio/ip/tcp.hpp>
#include <string>
#include "JobRequestQueue.h"

void serveJobRequest(boost::asio::ip::tcp::socket&, std::string&, JobRequestQueue&);
void sendResponses(boost::asio::ip::tcp::socket&,  JobRequestQueue&, const std::string&);

#endif //SERVER_JOBMANAGER_H
