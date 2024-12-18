#include <iostream>
#include "CommandLineOptions.hpp"
#include "FileManager.hpp"
#include "Hasher.hpp"

int main (int argc, char* argv[])
{
    support::CommandLineOptions commandLineOptions{};

    auto state = commandLineOptions.Parse(argc, argv);

    if (support::CommandLineOptions::State::Success == state)
    {
        support::Hasher hasher{};
        support::FileManager fileManager{};

        auto action = commandLineOptions.GetAction();
        auto textFilePath = commandLineOptions.GetTextFilePath();
        auto hashFilePath = commandLineOptions.GetHashFilePath();
        auto salt = commandLineOptions.GetSalt();

        if (support::CommandLineOptions::Action::Calculate == action)
        {
            auto content = fileManager.ReadString(textFilePath);
            auto hash = hasher.GetHash(content, salt);
            fileManager.WriteString(hashFilePath, hash);
        }
        else
        {
            auto content = fileManager.ReadString(textFilePath);
            auto hash = hasher.GetHash(content, salt);
            auto expectedHash = fileManager.ReadString(hashFilePath);

            if (hash != expectedHash)
            {
                std::cout << "Input file [" << textFilePath << "] was corrupted - expected checksum: " << expectedHash;
                std::cout << ", actual checksum: " << hash << std::endl;
                return 1;
            }
        }
    }
    else if (support::CommandLineOptions::State::Version == state)
    {
        std::cout << "v" << commandLineOptions.GetVersion() << std::endl;
    }
    else if (support::CommandLineOptions::State::Help == state)
    {
        std::cout << "Help: " << commandLineOptions.GetHelp() << std::endl;
    }
    else
    {
        std::cout << commandLineOptions.GetErrorMessage() << std::endl;
        return 2;
    }

    return 0;
}