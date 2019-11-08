#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../ArgsParser/argsParser.hpp"
#include "../StatProcessor/statProcessor.hpp"

#include <string>

class Application
{
public:
    explicit Application(const Arguments& arguments);

    void            run();


private:
    std::string         mFilePath;
    LogFile             mLogFile;
    StatProcessor       mStatProcessor;
};

#endif // APPLICATION_HPP
