#include <crypto++/cryptlib.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <crypto++/md5.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>
#include <fstream>
#include <filesystem>
#include "Checksum.h"

std::string computeChecksum(const std::string &path){
	CryptoPP::Weak1::MD5 hash;

	std::filesystem::directory_entry file{path};

	if(!file.exists()){
	    throw std::runtime_error("Checksum computation: file " + path + " does not exist");
	}

	const size_t size = CryptoPP::Weak1::MD5::DIGESTSIZE * 2;
	byte buf[size] = {0};
	CryptoPP::FileSource(
	        path.c_str(), true,
	        new CryptoPP::HashFilter(
	                hash, new CryptoPP::HexEncoder(new CryptoPP::ArraySink(buf, size))));
    std::string checksum = std::string(reinterpret_cast<const char*>(buf), size);

	return checksum;
}
