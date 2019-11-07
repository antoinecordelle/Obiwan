#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../ArgsParser/argsParser.hpp"
#include "../Processor/processor.hpp"

#include <string>

class Application
{
public:
    explicit Application(const Arguments& arguments);

    void            run();


private:
    std::string     mFilePath;
    Processor       mProcessor;
};

#endif // APPLICATION_HPP
