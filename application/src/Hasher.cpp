#include "Hasher.hpp"
#include <fstream>
#include <boost/algorithm/hex.hpp>

support::Hasher::Hasher() 
{
}

support::Hasher::~Hasher()
{
}

std::string support::Hasher::toString(const md5::digest_type &digest)
{
    const auto charDigest = reinterpret_cast<const char *>(&digest);
    std::string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
    return result;
}

std::string support::Hasher::GetHash(const std::string & content, const std::string salt)
{
    std::string contentPlusSalt{content + salt};
    md5 hash;
    md5::digest_type digest;
    hash.process_bytes(contentPlusSalt.data(), contentPlusSalt.size());
    hash.get_digest(digest);

    return toString(digest);
}