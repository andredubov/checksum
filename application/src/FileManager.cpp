#include "FileManager.hpp"
#include <fstream>

support::FileManager::FileManager()
{
}

support::FileManager::~FileManager()
{
}

void support::FileManager::WriteString(const std::string & filePath, const std::string & content)
{
    std::ofstream file(filePath, std::ios::trunc);

    if ( file.is_open() )
    {
        file << content << std::endl;
        file.flush();
    }

    file.close();
}

std::string support::FileManager::ReadString(const std::string & filePath)
{
    std::string content, line;
    std::ifstream file;

    file.open(filePath);

    if ( file.is_open() )
    {
        while ( std::getline(file, line) )
        {
            content.append(line);
        }
    }

    file.close();

    return content;
}