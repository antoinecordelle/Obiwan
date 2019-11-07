#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../ArgsParser/argsParser.hpp"

#include <string>

class Application
{
public:
    explicit Application(const Arguments& arguments);

    void            run();


private:
    std::string     mFile;
    int             mThreshold;
};

#endif // APPLICATION_HPP
