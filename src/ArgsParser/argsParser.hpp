#ifndef ARGSPARSER_HPP
#define ARGSPARSER_HPP

#include <string>

struct Arguments {
    std::string     filePath = "";
    int             threshold = 10;
    int             statFrame = 10;
    int             alertFrame = 120;
};

class ArgsParser {
public:
    static bool parseArgs(Arguments& args, int argc, char *argv[]);
};

#endif //ARGSPARSER_HPP
