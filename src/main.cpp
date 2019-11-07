#include "Application/application.hpp"
#include "ArgsParser/argsParser.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Arguments arguments;
    bool shouldRun = ArgsParser::parseArgs(arguments, argc, argv);
    if (shouldRun) {
        Application app(arguments);

        app.run();
    }


    return 0;
}
