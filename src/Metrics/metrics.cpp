#include "metrics.hpp"

Metric::Metric(time_t time)
        :mCounter(0)
        ,mStartTime(time)
{
}

void Metric::computeMetric() {

}

void Metric::updateMetric(const HttpPacket& packet) {

}

time_t Metric::getStartTime() {
    return mStartTime;
}
