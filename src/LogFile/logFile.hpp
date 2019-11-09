#ifndef LOGFILE_HPP
#define LOGFILE_HPP

#include <list>
#include "../Parser/parser.hpp"

class LogFile {
public:
    using ListIterator = std::list<HttpPacket>::iterator;

public:
    explicit                LogFile(const std::string& filePath);

    ListIterator            getBeginIte();
    void                    fetchLines(int numberOfLines);

private:
    void                    initialize();

private:
    Parser                  mParser;
    int                     mLineRange;
    std::list<HttpPacket>   mPacketList;
    bool                    isOver;
};


#endif //LOGFILE_HPP
