#include "Application/application.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    Arguments arguments;
    // parseArgs returns false if the argument "-h" was sent. It will then only display the help message.
    bool shouldRun = ArgsParser::parseArgs(arguments, argc, argv);
    if (shouldRun) {
        Application app(arguments);
        app.run();
    }
    return 0;
}
