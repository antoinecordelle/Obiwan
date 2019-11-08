#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <string>
#include "../Parser/parser.hpp"

class Processor {
public:
    Processor(const std::string& filePath, int threshold);

private:
    Parser          mParser;
    int             mThreshold;
};

#endif //PROCESSOR_HPP
