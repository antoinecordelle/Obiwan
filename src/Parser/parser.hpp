#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <fstream>
#include <tuple>
#include <list>

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
    /// Parses one line of the csv file mFile and returns the packet and a boolean indicating if the file is over
    /**
     * @return tuple<HttpPacket, bool> :
     * HttpPacket : log line parsed
     * bool : true if the file is over, which will trigger the end of the processing loop in Application. Else false
     */
    std::tuple<HttpPacket, bool>  parseOneLine();

private:
    std::ifstream   mFile;
};


#endif //PARSER_HPP
