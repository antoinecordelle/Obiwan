#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

struct HttpPacket {
    std::string     remoteHost;
    std::string     rfc931;
    std::string     authUser;
    time_t          date;
    std::string     request;
    int             status;
    int             bytes;
};

class Parser {
public:
    Parser(const std::string& filePath);

public:
    void            parseCsv();
    void            parseLine(std::string line);

private:
    std::string     mFilePath;
};


#endif //PARSER_HPP
