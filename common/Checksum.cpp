#include <crypto++/cryptlib.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <crypto++/md5.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>
#include <fstream>
#include "Checksum.h"

std::string computeChecksum(const std::string &path){
	CryptoPP::Weak1::MD5 hash;
	//TODO add checks if file exists
	  const size_t size = CryptoPP::Weak1::MD5::DIGESTSIZE * 2;
	  byte buf[size] = {0};
	  CryptoPP::FileSource(
		  path.c_str(), true,
		  new CryptoPP::HashFilter(
		      hash, new CryptoPP::HexEncoder(new CryptoPP::ArraySink(buf, size))));
	  std::string checksum = std::string(reinterpret_cast<const char*>(buf), size);
	return checksum;
}
