#include "parser.hpp"
#include "../Utility/utility.hpp"
#include "../Error/logErrorException.hpp"
#include <string>
#include <sstream>

using namespace std;

Parser::Parser(const std::string& filePath)
:mFile(filePath) {
    if (!mFile.is_open())
        throw invalid_argument("Unable to open file");

    string headers;
    // Remove first line : header with column names
    getline(mFile, headers);
}

Parser::~Parser() {
    if (mFile.is_open())
        mFile.close();
}

tuple<HttpPacket, bool> Parser::parseOneLine() {
    string line;
    HttpPacket httpPacket = HttpPacket();
    if( getline(mFile, line)) {
        int state(0);
        string field;
        istringstream lineStream(line);
        while (getline(lineStream, field, ',')) {
            switch (state) {
                case 0:
                    field = Utility::removeChar(field, '\"');
                    httpPacket.remoteHost = field;
                    break;
                case 1:
                    field = Utility::removeChar(field, '\"');
                    httpPacket.rfc931 = field;
                    break;
                case 2:
                    field = Utility::removeChar(field, '\"');
                    httpPacket.authUser = field;
                    break;
                case 3:
                    httpPacket.date = (time_t) stol(field);
                    break;
                case 4:
                    field = Utility::removeChar(field, '\"');
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
        return {httpPacket, false};
    }
    return {httpPacket, true};
}
