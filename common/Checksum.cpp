#include <crypto++/cryptlib.h>
#include <crypto++/sha.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>
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
	const size_t size = CryptoPP::SHA256::DIGESTSIZE * 2;
	byte buf[size] = {0};

	//computing checksum using CryptoPP library
    CryptoPP::SHA256 hash;
	CryptoPP::FileSource(
	        path.c_str(), true,
	        new CryptoPP::HashFilter(
	                hash, new CryptoPP::HexEncoder(new CryptoPP::ArraySink(buf, size))));

	//converting to string
	std::string checksum = std::string(reinterpret_cast<const char*>(buf), size);

	return checksum;
}
