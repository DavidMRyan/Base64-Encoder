#pragma once
#include <string>

namespace Utility
{
    class Binary
    {
    public:
        static std::string str2bin(const std::string &in);
        static int bin2dec(const std::string &in);
    };
}

