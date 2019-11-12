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
        if (string(argv[i]) == "-f" || string(argv[i]) == "--filePath") {
            if (i + 1 < argc) {
                args.filePath = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
            }
            else {
                std::cerr << "-f / --filePath option requires one argument." << std::endl;
            }
        } else if (string(argv[i]) == "-t" || string(argv[i]) == "--threshold") {
            if (i + 1 < argc) {
                args.threshold = stoi(argv[++i]);
            }
        }
    }
    if (args.filePath.empty()) {
        throw invalid_argument("Please provide a file name using the -f option");
    }
    return true;
}