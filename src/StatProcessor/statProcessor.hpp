#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <string>
#include <list>
#include "../Parser/parser.hpp"
#include "../LogFile/logFile.hpp"

class StatProcessor {
public:
    using ListIterator = std::list<HttpPacket>::iterator;

public:
    explicit StatProcessor(LogFile* logFile);

    void                    run();


private:
    LogFile*                mLogFilePtr;
    time_t                  mCurrentTime;
    ListIterator            mCurrentPosition;

};

#endif //PROCESSOR_HPP
