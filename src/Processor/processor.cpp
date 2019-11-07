#include "processor.hpp"

Processor::Processor(const std::string filePath, int threshold)
:mParser(filePath)
,mThreshold(threshold)
{

}
