#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <string>
#include <list>
#include <vector>
#include "../Parser/parser.hpp"
#include "../LogFile/logFile.hpp"
#include "../Metrics/metrics.hpp"

class StatProcessor {
public:
    using ListIterator = std::list<HttpPacket>::iterator;

public:
    StatProcessor() = default;

    bool processLine(const HttpPacket& httpPacket);
    std::vector<Metric> getMetrics(const HttpPacket& lastPacket);

private:
    Metric     mCurrentMetric{};
    Metric     mBufferedMetric{};
};

#endif //PROCESSOR_HPP
