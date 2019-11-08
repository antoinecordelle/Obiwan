#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <string>
#include <list>
#include "../Parser/parser.hpp"

class Processor {
public:
    Processor(const std::string& filePath, int threshold);

    void                    run();

private:
    bool                    fetchLines();

private:
    Parser                  mParser;
    int                     mThreshold;
    std::list<HttpPacket>   mPackets;
};

#endif //PROCESSOR_HPP
