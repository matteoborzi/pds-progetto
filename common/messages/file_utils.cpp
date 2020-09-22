#include <filesystem>
#include <fstream>
#include <boost/asio/write.hpp>
#include "file_utils.h"

#define BLOCK_SIZE 1024*4

void sendFile(boost::asio::ip::tcp::socket & socket,const std::string& path, size_t size){
    std::filesystem::directory_entry entry{path};
    if(!entry.exists() || !entry.is_regular_file() )
        throw std::logic_error(path+" does not exist");

    if( entry.file_size()!=size )
        throw std::runtime_error("Expecting "+path+" to be "+std::to_string(size) +" Bytes but is "+
        std::to_string(entry.file_size())+ " Bytes");

    std::ifstream file{path, std::ios::in | std::ios::binary};

    if(!file)
        throw std::runtime_error("Cannot open "+path);

    size_t bytes_read;
    char buf[BLOCK_SIZE];
    while((bytes_read=file.readsome(buf, BLOCK_SIZE))>0){
        boost::asio::write(socket, boost::asio::buffer(buf, bytes_read));
        size -= bytes_read;
    }
    if(size!=0)
        throw std::logic_error("The file "+path+ "has not been sent correctly");

    file.close();
}

void receiveFile(boost::asio::ip::tcp::socket &,const std::string&, size_t size){

}