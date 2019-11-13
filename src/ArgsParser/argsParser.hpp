#ifndef ARGSPARSER_HPP
#define ARGSPARSER_HPP

#include <string>

struct Arguments {
    std::string     filePath = "";
    // Number on average of hits per second
    int             threshold = 10;
    // Time frame of the statProcessor : metrics will be computed every statFrame second
    int             statFrame = 10;
    // Time frame of the alertHandler : alerts will be computed based on a alertFrame second wide window.
    int             alertFrame = 120;
};

class ArgsParser {
public:
    /// Parses the parameters entered in the CLI. Returns false if the -h parameter was entered, will display the help message
    static bool parseArgs(Arguments& args, int argc, char *argv[]);
};

#endif //ARGSPARSER_HPP
