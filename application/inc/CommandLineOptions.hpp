#ifndef COMMAND_LINE_OPTIONS_HPP
#define COMMAND_LINE_OPTIONS_HPP

#include <string>
#include <boost/program_options.hpp>

namespace support
{
    namespace po = boost::program_options;

    class CommandLineOptions
    {
    public:
        enum class State : int 
        {
            Success,
            Version,
            Help,
            Failure,
        };

        enum class Action : int
        {
            Calculate = 0,
            Check,
        };

        explicit CommandLineOptions();
        virtual ~CommandLineOptions();

        State Parse(int argc, char* argv[]);

        Action GetAction() const;
        virtual std::string GetTextFilePath() const;
        virtual std::string GetHashFilePath() const;
        virtual std::string GetHelp() const;
        virtual std::string GetVersion() const;
        virtual std::string GetErrorMessage() const;
        virtual std::string GetSalt() const;

    protected:
        virtual void Setup();
        virtual bool isFileValid(const std::string & filePath);

    private:
        CommandLineOptions(const CommandLineOptions& rhs);
        CommandLineOptions& operator=(const CommandLineOptions& rhs);

        po::options_description options;
        const std::string calculateAction;
        const std::string checkAction;
        std::string actionName;
        std::string textFilePath;
        std::string checkSumFilePath;
        std::string salt;
        std::string version;
        std::string help;
        std::string errorMessage;
    };
}

#endif // COMMAND_LINE_OPTION_HPP