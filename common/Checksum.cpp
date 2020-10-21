#include <crypto++/cryptlib.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <crypto++/md5.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>
#include <fstream>
#include <filesystem>
#include "Checksum.h"

/**
 * Compute the checksum of a file
 * @param path of the file
 * @return checksum
 * @throws runtime_error if file does not exists
 */
std::string computeChecksum(const std::string &path){


	std::filesystem::directory_entry file{path};
    //checking correctness of the path
	if(!file.exists() || !file.is_regular_file()){
	    throw std::runtime_error("Checksum computation: file " + path + " does not exist");
	}

    //computing size of the checksum
	const size_t size = CryptoPP::Weak1::MD5::DIGESTSIZE * 2;
	byte buf[size] = {0};

	//computing checksum using CryptoPP library
    CryptoPP::Weak1::MD5 hash;
	CryptoPP::FileSource(
	        path.c_str(), true,
	        new CryptoPP::HashFilter(
	                hash, new CryptoPP::HexEncoder(new CryptoPP::ArraySink(buf, size))));

	//converting to string
	std::string checksum = std::string(reinterpret_cast<const char*>(buf), size);

	return checksum;
}
