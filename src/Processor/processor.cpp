#include "processor.hpp"

using namespace std;

Processor::Processor(const string& filePath, int threshold)
:mParser(filePath)
,mThreshold(threshold)
{

}

void Processor::run() {
    bool isOver(false);
    while (!isOver)
    {
        isOver = fetchLines();
    }

}

bool Processor::fetchLines() {
    auto [lines, isOver] = mParser.parseLines(50);
    mPackets.splice(mPackets.end(), lines);
    return isOver;
}
