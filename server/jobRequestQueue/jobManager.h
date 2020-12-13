#ifndef SERVER_JOBMANAGER_H
#define SERVER_JOBMANAGER_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <string>
#include "JobRequestQueue.h"

void serveJobRequest(boost::asio::ip::tcp::socket&, std::string&, JobRequestQueue&);
void sendResponses(boost::asio::ip::tcp::socket&,  JobRequestQueue&, const std::string&,
                   std::atomic_bool&, std::atomic_bool&, const std::string&);

#endif //SERVER_JOBMANAGER_H
