#include "logFile.hpp"
#include <iostream>

using namespace std;

LogFile::LogFile(const string& filePath)
        :mParser(filePath)
        ,mLineRange(50)
        ,isOver(false)
{
    initialize();
}

void LogFile::initialize()
{
    fetchLines(mLineRange);
}

LogFile::ListIterator LogFile::getBeginIte() {
    return mPacketList.begin();
}

void LogFile::fetchLines(int numberOfLines) {
    auto [lines, over] = mParser.parseLines(numberOfLines);
    mPacketList.splice(mPacketList.end(), lines);
    isOver = over;
}
