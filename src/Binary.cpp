#include "./Binary.hpp"

/**
 * \brief Converts a string to binary.
 * \param in Input string.
 * \return Binary value of the input string.
 */
std::string Utility::Binary::str2bin(const std::string &in)
{
    std::string output = "";
    int bits[8];
    
    for (char c : in)
    {
        for (int& bit : bits)
        {
            bit = c % 2;
            c /= 2;
        }

        // Fill string with concatenated binary digits
        for (int b = 0, a = 7; b < 8; b++, a--)
            output += std::to_string(bits[a]);
    }

    return output;
}

/**
 * \brief Converts an input binary value to a decimal value.
 * \param in Input binary value.
 * \return Decimal value of the input binary value.
 */
int Utility::Binary::bin2dec(const std::string &in)
{
    const int input = std::stoi(in);
    int decimal = 0;
    int base = 1;

    int temp = input;
    while (temp)
    {
        int ldigit = temp % 10;
        temp /= 10;
        decimal += ldigit * base;
        base *= 2;
    }

    return decimal;
}