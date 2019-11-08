#include "parser.hpp"
#include "../Utility/utility.hpp"
#include "../Error/logErrorException.hpp"
#include <string>
#include <sstream>

using namespace std;

Parser::Parser(const std::string& filePath)
: mFile(filePath)
{
    if (mFile.is_open())
    {
        string headers;
        // Remove first line : header with column names
        getline(mFile, headers);
    }
    else
        throw invalid_argument("Unable to open file");
}

Parser::~Parser()
{
    if (mFile.is_open())
        mFile.close();
}

void Parser::parseCsv() {
    string line;
    if (mFile.is_open())
    {
        while ( getline (mFile,line) )
        {
            parseLine();
        }
        mFile.close();
    }
    else
        throw invalid_argument("Unable to open file");
}

HttpPacket Parser::parseLine() {
    string line;
    getline(mFile, line);

    int state(0);
    string field;
    HttpPacket httpPacket;
    istringstream lineStream(line);
    while (getline(lineStream, field, ',')) {
        switch (state) {
            case 0:
                Utility::removeChar(field, '\"');
                httpPacket.remoteHost = field;
                break;
            case 1:
                Utility::removeChar(field, '\"');
                httpPacket.rfc931 = field;
                break;
            case 2:
                Utility::removeChar(field, '\"');
                httpPacket.authUser = field;
                break;
            case 3:
                httpPacket.date = (time_t) stol(field);
                break;
            case 4:
                Utility::removeChar(field, '\"');
                httpPacket.request = field;
                break;
            case 5:
                httpPacket.status = stoi(field);
                break;
            case 6:
                httpPacket.bytes = stoi(field);
                break;
            default:
                throw LogErrorException();
        }
        state++;
    }
    return httpPacket;
}
