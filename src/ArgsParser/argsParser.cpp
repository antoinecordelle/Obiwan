#include <iostream>
#include <string>
#include "argsParser.hpp"

using namespace std;

bool ArgsParser::parseArgs(Arguments &args, int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-h" || string(argv[i]) == "--help") {
            cout << "Help" << endl;
            return false;
        }
        if (string(argv[i]) == "-f" || string(argv[i]) == "--file") {
            if (i + 1 < argc) {
                args.file = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
            }
            else {
                std::cerr << "-f / --file option requires one argument." << std::endl;
            }
        } else if (string(argv[i]) == "-t" || string(argv[i]) == "--threshold") {
            if (i + 1 < argc) {
                args.threshold = atoi(argv[i++]);
            }
        }
    }
    if (args.file.empty()) {
        throw invalid_argument("Please provide a file name using the -f option");
    }
    return true;
}