#include "processor.hpp"

using namespace std;

Processor::Processor(const string& filePath, int threshold)
:mParser(filePath)
,mThreshold(threshold)
{
    HttpPacket httpPacket = mParser.parseLine();
}
