#include "statProcessor.hpp"
#include <iostream>

using namespace std;

bool StatProcessor::processLine(const HttpPacket& httpPacket) {
    if (mCurrentMetric.getStartTime() + 10 > httpPacket.date)
    {
        mCurrentMetric.updateMetric(httpPacket);
        return false;
    }
    else
    {
        mBufferedMetric = mCurrentMetric;

        // The new metric will start in the beginning of the 10sec window where the new packet belongs
        // Knowing that the first window begins at the time of the first line.
        // This gets the number of 10sec chunks between the last computed metric and the next packet.
        long newStartModifier((httpPacket.date - mBufferedMetric.getStartTime() - 10)/10);
        time_t newStart(mBufferedMetric.getStartTime() + 10 *(newStartModifier + 1));
        mCurrentMetric = Metric(newStart);

        mCurrentMetric.updateMetric(httpPacket);
    }
}

std::vector<Metric> StatProcessor::getMetrics(const HttpPacket& lastPacket) {
    mBufferedMetric.computeMetric();
    auto completedMetrics = vector<Metric>{mBufferedMetric};
    // Number of chunks of 10sec where no data has been received
    long emptyMetricsCount((mCurrentMetric.getStartTime() - mBufferedMetric.getStartTime())/10);
    completedMetrics.insert(completedMetrics.end(), emptyMetricsCount, Metric());
    return completedMetrics;
}
