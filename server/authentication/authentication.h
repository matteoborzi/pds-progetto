#ifndef SERVER_AUTHENTICATION_H
#define SERVER_AUTHENTICATION_H

#include <string>

std::optional<std::string> doAuthentication(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&);


#endif //SERVER_AUTHENTICATION_H
