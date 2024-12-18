#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>

namespace support
{
    class FileManager
    {
    public:
        explicit FileManager();
        virtual ~FileManager();

        virtual void WriteString(const std::string & filePath, const std::string & content);
        virtual std::string ReadString(const std::string & filePath);
    };
}

#endif // FILE_MANAGER_HPP