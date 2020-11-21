#include "connection_utils.h"

void run(boost::asio::ip::tcp::socket& socket,
         std::chrono::steady_clock::duration timeout,
         boost::asio::io_context& io_context);

void custom_handshake(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket_stream,
                      std::chrono::steady_clock::duration timeout,
                      boost::asio::io_context& io_context){

    // Start the asynchronous operation itself. The lambda that is used as a
    // callback will update the error variable when the operation completes.
    boost::system::error_code error;
    socket_stream.async_handshake(boost::asio::ssl::stream_base::client,
                                  [&](const boost::system::error_code& result_error)
                                  {
                                      error = result_error;
                                  });
    // Run the operation until it completes, or until the timeout.
    run(socket_stream.next_layer(), timeout, io_context);

    // Determine whether a connection was successfully established.
    if (error)
        throw std::system_error(error);

}

void custom_connect(boost::asio::ip::tcp::socket &socket,
             boost::asio::ip::tcp::endpoint &endpoint,
             std::chrono::steady_clock::duration timeout,
             boost::asio::io_context& io_context){

    // Start the asynchronous operation itself. The lambda that is used as a
    // callback will update the error variable when the operation completes.
    boost::system::error_code error;
    socket.async_connect( endpoint,
                               [&](const boost::system::error_code& result_error)
                               {
                                   error = result_error;
                               });
    // Run the operation until it completes, or until the timeout.
    run(socket, timeout, io_context);

    // Determine whether a connection was successfully established.
    if (error)
        throw std::system_error(error);
}

void run(boost::asio::ip::tcp::socket& socket,
         std::chrono::steady_clock::duration timeout,
         boost::asio::io_context& io_context){

    // Restart the io_context, as it may have been left in the "stopped" state
    // by a previous operation.
    io_context.restart();

    // Block until the asynchronous operation has completed, or timed out
    io_context.run_for(timeout);

    // If the asynchronous operation completed successfully then the io_context
    // would have been stopped due to running out of work. If it was not
    // stopped, then the io_context::run_for call must have timed out.
    if (!io_context.stopped()) {
        // Close the socket to cancel the outstanding asynchronous operation.
        socket.close();
        // Run the io_context again until the operation completes.
        io_context.run();
    }
}



