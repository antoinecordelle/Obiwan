#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <string>
#include <list>
#include <vector>
#include "../Parser/parser.hpp"
#include "../Metrics/metrics.hpp"

class StatProcessor {
public:
    using ListIterator = std::list<HttpPacket>::iterator;

public:
    explicit StatProcessor(int timeWindow);

    void initialize(const HttpPacket &httpPacket);
    bool processLine(const HttpPacket &httpPacket);
    std::vector<Metric> getMetrics();
    Metric getLastMetric();

private:
    Metric     mCurrentMetric{};
    Metric     mBufferedMetric{};
    int        mTimeWindow;
};

#endif //PROCESSOR_HPP
