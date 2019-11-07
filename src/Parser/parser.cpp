#include "parser.hpp"
#include <string>
#include <fstream>

using namespace std;

Parser::Parser(const std::string& filePath)
: mFilePath(filePath)
{
}


void Parser::parseCsv() {
    string line;
    ifstream file(mFilePath);
    if (file.is_open())
    {
        // Remove first line : header with column names
        getline(file, line);
        while ( getline (file,line) )
        {
            parseLine(line);
        }
        file.close();
    }
    else
        throw invalid_argument("Unable to open file");
}

void Parser::parseLine(std::string line) {

}
