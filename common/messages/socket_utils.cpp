#include "socket_utils.h"

/**
 * Terminate all communications on the socket and closes it
 * @param the socket to terminate
 */
void close_socket(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket){
    try {
        socket.next_layer().shutdown(boost::asio::socket_base::shutdown_both);
        socket.next_layer().close();
    }catch(...){
        //socket already closed
    };
}