#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <thread>
#include <filesystem>
#include <boost/algorithm/string.hpp>
#include <boost/asio/ssl.hpp>

#include "waiter/Waiter.h"
#include "pathPool/PathPool.h"
#include "authentication/authentication.h"
#include "jobRequestQueue/JobRequestQueue.h"
#include "ChecksumStorage/ChecksumStorage.h"

#include "../common/messages/socket_utils.h"
#include "../common/messages/file_utils.h"
#include "log/log_utils.h"

#include "Workspace/load.h"
#include "jobRequestQueue/jobManager.h"


bool restore(boost::asio::ssl::stream<boost::asio::ip::tcp::socket> &, const std::string &);

int main(int argc, char *argv[]) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;
    int port;

    // Parameters check
    // Usage: <server_port>
    if (argc < 2) {
        std::cerr << "Not enough arguments: port_number is missing" << std::endl;
        return 1;
    }

    // Checking type of port parameter
    try {
        port = std::stoi(argv[1]);
    } catch (std::exception &e) {
        std::cerr << "Invalid port argument: not a number" << std::endl;
        return 2;
    }

    // SSL connection setup
    boost::asio::io_context my_context;
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    boost::asio::ip::tcp::acceptor acceptor(my_context, endpoint);

    ssl_context.set_options(
            boost::asio::ssl::context::default_workarounds
            | boost::asio::ssl::context::no_sslv2
            | boost::asio::ssl::context::single_dh_use);

    ssl_context.use_certificate_chain_file("../cert/server.cert.pem");
    ssl_context.use_private_key_file("../cert/server.key.pem", boost::asio::ssl::context::pem);
    
    std::cout << "Server has started on port " << port << std::endl;

    while (true) {
        // Reserve server resources through an instance of Waiter
        std::shared_ptr<Waiter> w = std::make_shared<Waiter>();

        std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket =
                std::make_shared<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(my_context, ssl_context);

        acceptor.accept(socket->next_layer());

        // Get IP address for logs
        std::string ipaddr = socket->next_layer().remote_endpoint().address().to_string();
        print_log_message(ipaddr, "Connection accepted");

        // Perform the connection
        try {
            socket->handshake(boost::asio::ssl::stream_base::server);
        } catch (std::exception &e) {
            print_log_error(ipaddr, "Unable to perform TLS handshake");
            continue;
        }

        // Thread creation for a single request
        print_log_message(ipaddr, "Creating the thread");
        std::thread thread{[w, ipaddr, socket]() -> void {
            boost::asio::ssl::stream<boost::asio::ip::tcp::socket> &s = *socket;
            try {
                // User authentication
                std::optional<std::string> username = doAuthentication(s);
                if (username.has_value()) {
                    print_log_message(ipaddr, username.value(), "Successfully logged in");

                    // Load the workspace on server either in backup mode or in restore mode
                    std::shared_ptr<PathPool> poolItem = loadWorkspace(s, username.value());
                    if (poolItem->isValid()) {
                        std::string path = poolItem->getPath();
                        switch (poolItem->getRestore()) {
                            case true:
                                // Performing restore
                                bool restoreStatus;
                                restoreStatus = restore(s, path);
                                if (restoreStatus)
                                    // Restore ended correctly
                                    print_log_message(ipaddr, username.value(), "Restore completed");
                                else
                                    // Restore ended with errors
                                    print_log_message(ipaddr, username.value(), "Restore failed");
                                break;
                            case false:

                                std::atomic_bool stopped_mine = false, stopped_other = false;
                                std::condition_variable terminated;

                                // Performing backup
                                // Another thread is created: the first one reads the requests from the socket,
                                // while the other one digests them
                                JobRequestQueue queue{};
                                std::thread responder{sendResponses, std::ref(s), std::ref(queue), std::cref(path),
                                                      std::ref(stopped_mine), std::ref(stopped_other), std::ref(username.value())};
                                while (!stopped_mine && !stopped_other) {
                                    try {
                                        serveJobRequest(s, path, queue);
                                    } catch (std::exception &e) {
                                        print_log_error(ipaddr, username.value(), e.what());
                                        // Interrupting other thread
                                        stopped_mine = true;
                                    }
                                }
                                if (stopped_mine) {
                                    // Adding a fictional job to awake other thread if sleeping
                                    BackupPB::JobRequest empty_req{};
                                    queue.enqueueJobRequest(empty_req);
                                }

                                responder.join();
                                print_log_message(ipaddr, username.value(), "Terminating the connection");
                        }

                    } else {
                        print_log_message(ipaddr, username.value(), "Failed to connect to the workspace");
                    }

                } else print_log_message(ipaddr, "Failed to log in");

            } catch (std::exception &e) {
                print_log_error(ipaddr, e.what());
            }

            return;
        }};
        thread.detach();

    }

//    return 1;
}

/**
 * Function that performs the restore functionality server-side.
 * The function checks recursively and creates a request for each directory entry in the restore path,
 * then sends them to the client through the socket.
 * @param socket to send/receive messages
 * @param path to restore
 * @return true if restore has been performed successfully
 */
bool restore(boost::asio::ssl::stream<boost::asio::ip::tcp::socket> &socket, const std::string &path) {
    // Get IP address for log purposes
    std::string ipaddr = socket.next_layer().remote_endpoint().address().to_string();

    // For each entry in the workspace create a JobRequest
    for (std::filesystem::directory_entry entry : std::filesystem::recursive_directory_iterator(path)) {
        BackupPB::JobRequest request{};
        if (entry.is_directory())
            request.set_pbaction(BackupPB::JobRequest_PBAction_ADD_DIRECTORY);
        else if (entry.is_regular_file()) {
            request.set_pbaction(BackupPB::JobRequest_PBAction_ADD_FILE);
            request.set_size(entry.file_size());
        }

        // Compute the correct client path
        std::string path_to_send = entry.path();
        boost::algorithm::erase_first(path_to_send, path);
        request.set_path(path_to_send);

        // Try to send a JobRequest to client on the socket and eventually sends the relative file
        // Returns if write fails
        try {
            writeToSocket(socket, request);
            if (request.pbaction() == BackupPB::JobRequest_PBAction_ADD_FILE)
                sendFile(socket, entry.path(), request.size());
        }
        catch (std::exception &e) {
            //print_log_error(ipaddr,e.what());
            return false;
        }
    }
    BackupPB::JobRequest end{};
    end.set_pbaction(BackupPB::JobRequest_PBAction_END_RESTORE);
    end.set_path(" ");
    try {
        writeToSocket(socket, end);
    }
    catch (std::exception &e) {
        //print_log_error(ipaddr,e.what());
        return false;
    }

    return true;
}

