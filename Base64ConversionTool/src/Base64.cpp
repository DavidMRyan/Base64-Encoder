#include <iostream>
#include <regex>
#include <vector>
#include <bitset>

#include "Base64.hpp"
#include "Binary.hpp"

/**
 * \brief Encodes an input string in base64.
 * \param input Input string to be encoded in base64.
 * \return Base64 encoded string.
 * Reference: https://base64.guru/learn/base64-algorithm/encode
 */
std::string Utility::Base64::encode(const std::string &input)
{
    const uint64_t len = input.length();    
    const uint64_t remainder = len % 6;
    const uint64_t padding = !remainder ? 0 : 6 - remainder;
    uint64_t gsize = ((len + padding) / 6) + 1;
    std::vector<std::string> bitGroups(gsize);
    
    uint64_t lpos = 0, lgindex = 0;
    for(uint64_t pos = 0; pos <= len - remainder; pos += 6)
    {
        uint64_t gindex = pos / 6;
        const std::string temp = input.substr(pos, 6);
        bitGroups[gindex] = temp;

        // Keep track of final positions for use when adding remainder values.
        lpos = pos;
        lgindex = gindex;
    }

    // Handle remainders and padding
    std::string result = "";
    if(remainder != 0)
    {
        std::string temp = input.substr(lpos, remainder);
        while (temp.length() < 6) temp.push_back('0');
        bitGroups[lgindex] = temp;
    }
    
    // Convert 6 bit-bytes to 8 bit-bytes
    for (std::string &group : bitGroups)
        group.insert(0, "00");

    // Convert binary chunks to decimal values
    for(uint64_t i = 0; i < gsize; i++)
        result += dec2base64(Binary::bin2dec(bitGroups[i]));

    result.pop_back();
    return result;
}

std::string Utility::Base64::dec2base64(const int& decimal)
{
    // Convert the decimal value to binary and pad with zeros to ensure a length
    // that is a multiple of 6 (the length required for base64 encoding).
    const std::bitset<24> bin(decimal);
    std::string str = bin.to_string();
    str.insert(0, 24 - str.length(), '0');

    // Encode the binary value in base64 using the standard base64 encoding
    // characters and padding character ('=').
    const std::string dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string result;
    for (uint64_t i = 0; i < str.length(); i += 6)
    {
        std::string chunk = str.substr(i, 6);
        const uint32_t index = std::bitset<6>(chunk).to_ulong();
        result += dictionary[index];
    }
    result.append((3 - str.length() % 3) % 3, '=');

    // Remove any extraneous line breaks or whitespace characters from the
    // base64 string (not strictly necessary, but may be desired in some cases).
    return std::regex_replace(result, std::regex("\\s+"), "").substr(3, 1);
}
