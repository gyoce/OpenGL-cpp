#include "Utils.hpp"

#include <fstream>
#include <iostream>

std::string Utils::GetFileContent(const std::string& path) 
{
    std::ifstream file{ path };

    if (file.fail()) 
    {
        std::cerr << "Error while trying to open file : " << path << "\n";
        exit(EXIT_FAILURE);
    }

    std::string content;
    try 
    {
        file.seekg(0, std::ios::end);
        content.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(content.data(), content.size());
        file.close();
        return content;
    }
    catch(const std::exception& ex)
    {
        std::cerr << "Exception while reading file : " << ex.what() << "\n";
        exit(EXIT_FAILURE);
    }
}