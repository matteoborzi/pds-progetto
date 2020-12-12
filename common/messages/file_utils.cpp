#include <filesystem>
#include <fstream>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include "file_utils.h"

#define BLOCK_SIZE 1024 // Size of each chunk that can be sent on the net

/**
 * Send a file on the network
 * @param socket to send data
 * @param path of the file
 * @param size of the file
 * @throws logic_error if file does not exists
 * @throws runtime_error if size is different from the expected one,
 *          file is not available or error occurred on the network
 * @throws boost::system::system_error if a network communication error occurs
 */
void sendFile(boost::asio::ssl::stream<boost::asio::ip::tcp::socket> &socket, const std::string &path, size_t size) {
    //check on file existence
    std::filesystem::directory_entry entry{path};


    bool invalid_file = false;
    //check on file size
    if (entry.file_size() != size || !entry.exists() || !entry.is_regular_file())
        invalid_file = true;




    //file is read in blocks, which are sent sequentially on the network
    size_t bytes_read;
    //creating a block
    char buf[BLOCK_SIZE] = {};
    if (invalid_file) {
        while (size > 0) {
            size_t len = size > BLOCK_SIZE ? BLOCK_SIZE : size;
            boost::asio::write(socket, boost::asio::buffer(buf, len));
            size -= len;
        }
    } else {
        std::ifstream file{path, std::ios::in | std::ios::binary};

        if (!file)
            throw std::runtime_error("Cannot open " + path);
        while ((bytes_read = file.read(buf, BLOCK_SIZE).gcount()) > 0) {
            size_t bytes_written = boost::asio::write(socket, boost::asio::buffer(buf, bytes_read));
            if (bytes_written != bytes_read)
                throw std::runtime_error("Cannot write expected number of bytes of file");
            size -= bytes_read;
        }
        file.close();
    }


    //checking if the expected number of bytes has been sent on the network
    if (size != 0)
        throw std::logic_error("The file " + path + " has not been sent correctly");

}

/**
 * Receive data from the network and save them into a file
 * @param socket from which get data
 * @param path where store the file
 * @param size of the file to receive
 * @throws runtime_error if file cannot be created
 * @throws boost::system::system_error if a network communication error occurs
 */
void receiveFile(boost::asio::ssl::stream<boost::asio::ip::tcp::socket> &socket, const std::string &path, size_t size) {

    std::ofstream file{path, std::ios::out | std::ios::binary};
    //check file opening (and creation)
    if (!file)
        throw std::runtime_error("Cannot create " + path);

    //allocating block
    char buf[BLOCK_SIZE];

    while (size > 0) {
        //computing number of bytes to read (a block or the residual)
        size_t byte_to_read = size > BLOCK_SIZE ? BLOCK_SIZE : size;

        //reading bytes from network
        size_t bytes_read = boost::asio::read(socket, boost::asio::buffer(buf, byte_to_read));
        if (bytes_read != byte_to_read)
            throw std::runtime_error("Cannot read expected number of bytes of file");

        //storing bytes in the file
        file.write(buf, byte_to_read);

        //decrementing bytes to read
        size -= byte_to_read;
    }
    file.close();

}