#include <boost/filesystem.hpp>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "CommandLineOptions.hpp"

support::CommandLineOptions::CommandLineOptions() :
    options(),
    calculateAction("calc"),
    checkAction("check"),
    actionName(calculateAction),
    textFilePath(),
    checkSumFilePath(),
    salt("sec3r2eT_sa432Lt_2=V"),
    version("0.0.0"),
    help(),
    errorMessage()
{
    Setup();
}

support::CommandLineOptions::~CommandLineOptions()
{
}

void support::CommandLineOptions::Setup()
{
    po::options_description general_options("General options");
    po::options_description specific_options("Specific options");

    general_options.add_options()
        ("version", "Show version")
        ("help", "Show help");

    specific_options.add_options()
        ("action", po::value<std::string>(&actionName), "Select action: check or calc")
        ("file", po::value<std::string>(&textFilePath), "Input file path")
        ("checksum-file", po::value<std::string>(&checkSumFilePath), "Checksum file path")
        ("salt", po::value<std::string>(&salt), "Salt to hash an input file content");

    options.add(general_options);
    options.add(specific_options);
}

support::CommandLineOptions::State support::CommandLineOptions::Parse(int argc, char* argv[])
{
    auto state = State::Success;
    try
    {
        po::variables_map variableMap;
        po::parsed_options parsed = po::parse_command_line(argc, argv, options);
        po::store(parsed, variableMap);
        po::notify(variableMap);

        if (variableMap.count("help"))
        {
            std::stringstream ss;
            ss << options;
            help = ss.str();
                    
            return State::Help;
        }

        if (variableMap.count("version"))
        {
            return State::Version;
        }

        if (0 == variableMap.count("action"))
        {
            errorMessage = "ERROR: missing an argument for the option [--action].";
            return State::Failure;
        }

        if (variableMap.count("file"))
        {
            state = isFileValid(textFilePath) ? State::Success : State::Failure;
        }
        else 
        {
            errorMessage = "ERROR: missing an argument for the option [--file].";
            return State::Failure;
        }

        if (variableMap.count("checksum-file"))
        {
            std::transform(actionName.begin(), actionName.end(), actionName.begin(), [](unsigned char c) {
                return std::tolower(c);
            });

            if (actionName == checkAction)
            {
                state = isFileValid(checkSumFilePath) ? State::Success : State::Failure;
            }
        }
        else
        {
            errorMessage = "ERROR: missing an argument for the option [--checksum-file].";
            return State::Failure;
        }
    }
    catch (const std::exception& e)
    {
        errorMessage = "ERROR: parser error [" + std::string(e.what()) + "].";
        state = State::Failure;
    }
    catch (...)
    {
        errorMessage = "ERROR: parsing error (unknown type).";
        state = State::Failure;
    }

    return state;
}

bool support::CommandLineOptions::isFileValid(const std::string & filePath)
{
    if (!boost::filesystem::is_regular_file(filePath))
    {
        errorMessage = "ERROR - provided file doesn't exist! [" +  filePath  + "]";
        return false;
    }

    return true;
}

support::CommandLineOptions::Action support::CommandLineOptions::GetAction() const
{
    return ((actionName == calculateAction) ? Action::Calculate : Action::Check);
}

std::string support::CommandLineOptions::GetTextFilePath() const
{
    return textFilePath;
}

std::string support::CommandLineOptions::GetHashFilePath() const
{
    return checkSumFilePath;
}

std::string support::CommandLineOptions::GetHelp() const
{
    return help;
}

std::string support::CommandLineOptions::GetVersion() const
{
    return version;
}

std::string support::CommandLineOptions::GetSalt() const
{
    return salt;
}

std::string support::CommandLineOptions::GetErrorMessage() const
{
   return errorMessage;
}