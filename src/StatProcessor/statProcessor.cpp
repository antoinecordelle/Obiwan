#include "statProcessor.hpp"
#include <iostream>

using namespace std;

StatProcessor::StatProcessor(int timeWindow)
:mTimeWindow(timeWindow){}

void StatProcessor::initialize(const HttpPacket &httpPacket) {
    mCurrentMetric = Metric(httpPacket.date);
}

bool StatProcessor::processLine(const HttpPacket &httpPacket) {
    if (mCurrentMetric.getStartTime() + mTimeWindow > httpPacket.date) {
        mCurrentMetric.updateMetric(httpPacket);
        return false;
    } else {
        mBufferedMetric = mCurrentMetric;

        // The new metric will start in the beginning of the 10sec window where the new packet belongs
        // Knowing that the first window begins at the time of the first line.
        // This gets the number of 10sec chunks between the last computed metric and the next packet.
        long newStartModifier((httpPacket.date - mBufferedMetric.getStartTime() - mTimeWindow) / mTimeWindow);
        time_t newStart(mBufferedMetric.getStartTime() + mTimeWindow * (newStartModifier + 1));
        mCurrentMetric = Metric(newStart);
        mCurrentMetric.updateMetric(httpPacket);

        return true;
    }
}

std::vector<Metric> StatProcessor::getMetrics() {
    mBufferedMetric.computeMetric();
    auto completedMetrics = vector<Metric>{mBufferedMetric};
    // Number of chunks of 10sec where no data has been received
    long emptyMetricsCount((mCurrentMetric.getStartTime() - mBufferedMetric.getStartTime() - mTimeWindow) / mTimeWindow);
    for (unsigned long i = 0; i < emptyMetricsCount; i++) {
        completedMetrics.emplace_back(mBufferedMetric.getStartTime() + mTimeWindow * (i + 1));
    }
    return completedMetrics;
}

Metric StatProcessor::getLastMetric() {
    mCurrentMetric.computeMetric();
    return mCurrentMetric;
}



