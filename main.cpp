#include <iostream>
#include <regex>
#include <string>
#include <conio.h>
#include <fstream>

#include "src/Base64.hpp"
#include "src/Binary.hpp"

int main(int argc, char** argv)
{
    std::string input = "";
    bool hasOutfile = false;
    
    if(argc > 1)
    {
        std::ifstream ifs;
        ifs.open (argv[1]);
        std::string line;
        hasOutfile = true;
        
        while(ifs && ifs.is_open())
        {
            std::getline(ifs, line);
            input += line;
        }
        
        ifs.close();
    }
    else
    {
        std::cout << "Please enter text to be encoded in base64: ";
        std::getline(std::cin, input);
    }
    
    std::string output = Utility::Binary::str2bin(input);
    std::cout << "Input String: " << input << std::endl;
    std::cout << "Base64 Output: " << Utility::Base64::encode(output) << std::endl;

    if(hasOutfile)
    {
        std::ofstream ofs("ENCODED_OUTPUT.txt");
        ofs << Utility::Base64::encode(output) << std::endl;
        ofs.close();
    }
    
    // Debug
    // std::cout << "Input -> Binary Digits -> as String: " << output << std::endl;
    // std::cout << "Binary Length: " << output.length() << std::endl;

    std::cout << std::endl << "Finished!";
    _getch();
    return 0;
}