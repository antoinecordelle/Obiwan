#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <fstream>

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
    explicit Parser(const std::string& filePath);
    ~Parser();

public:
    void            parseCsv();
    HttpPacket      parseLine();

private:
    std::ifstream   mFile;
};


#endif //PARSER_HPP
