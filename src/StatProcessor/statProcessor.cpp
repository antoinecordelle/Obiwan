#include "statProcessor.hpp"
#include <iostream>

using namespace std;

StatProcessor::StatProcessor(LogFile* logFile)
:mLogFilePtr(logFile)
,mCurrentPosition(logFile->getBeginIte())
{

}

void StatProcessor::run() {
}

