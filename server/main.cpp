#include <boost/asio/ip/tcp.hpp>
#include <iostream>


int main() {

    boost::asio::io_service my_context;

    boost::asio::ip::tcp::acceptor acceptor(my_context);
    //TODO porta da linea di comando
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 8080);
    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();
    std::cout<<"I'm listening"<<std::endl;

    while(true) {
        boost::asio::ip::tcp::socket socket(my_context);

        acceptor.accept(socket);
        std::cout << "Get a connection" << std::endl;
    }


    return 1;
}
