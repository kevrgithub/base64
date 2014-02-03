#ifndef BASE64_HPP
#define BASE64_HPP

#include <string>
#include <sstream>

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>

std::string base64_encode(const std::string& s)
{
    namespace bai = boost::archive::iterators;

    typedef bai::base64_from_binary<bai::transform_width<const char *, 6, 8> > base64_enc;

    std::stringstream os;

    std::copy
    (
        base64_enc(s.c_str()),
        base64_enc(s.c_str() + s.size()),
        bai::ostream_iterator<char>(os)
    );

    const std::string base64_padding[] = {"", "==", "="};

    os << base64_padding[s.size() % 3];

    return os.str();
}

std::string base64_decode(const std::string& s)
{
    namespace bai = boost::archive::iterators;

    typedef bai::transform_width<bai::binary_from_base64<const char *>, 8, 6> base64_dec;

    unsigned int size = s.size();

    if (size <= 0)
    {
        return "";
    }

    for (int i = 1; i <= 2; i++)
    {
        if (s.c_str()[size - 1] == '=')
        {
            size--;
        }
    }

    std::stringstream os;
    std::copy
    (
        base64_dec(s.c_str()),
        base64_dec(s.c_str() + size),
        bai::ostream_iterator<char>(os)
    );

    return os.str();
}

#endif // #define BASE64_HPP
