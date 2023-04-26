#pragma once
#include <string>
#include <vector>

namespace Utility
{
    class Base64
    {
    public:
        static std::string encode(const std::string &input);
        static std::string dec2base64(const int& decimal);
    };
}

