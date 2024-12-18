#ifndef HASHER_HPP
#define HASHER_HPP

#include <string>
#include <boost/uuid/detail/md5.hpp>
#include "FileManager.hpp"

namespace support
{
    using boost::uuids::detail::md5;

    class Hasher
    {
    public:
        explicit Hasher();
        virtual ~Hasher();
        virtual std::string GetHash(const std::string & content, const std::string salt);

    protected:
        virtual std::string toString(const md5::digest_type &digest);

    private:
        Hasher(const Hasher & rhs);
        Hasher& operator=(const Hasher& rhs);
    };
}

#endif // HASHER_HPP