#include "metrics.hpp"

Metric::Metric(time_t time)
        :mCounter(0)
        ,mStartTime(time)
{
}

void Metric::computeMetric() {

}

void Metric::updateMetric(const HttpPacket& packet) {
    mCounter++;
}

time_t Metric::getStartTime() {
    return mStartTime;
}

int Metric::getCounter() const {
    return mCounter;
}
