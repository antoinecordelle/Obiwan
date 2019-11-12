#include "metric.hpp"
#include "../Utility/utility.hpp"

using namespace std;

Metric::Metric(time_t time)
:mCounter(0)
,mStartTime(time)
{
}

void Metric::computeMetric() {
    mMostHitResource = Utility::findMaxValue<string, int>(mResourceHits);
}

void Metric::updateMetric(const HttpPacket& packet) {
    mCounter++;
    string resourceHit = Utility::getResource(packet);
    mResourceHits[resourceHit] += 1;
}

time_t Metric::getStartTime() {
    return mStartTime;
}

int Metric::getCounter() const {
    return mCounter;
}

pair<std::string, int> Metric::getMostHitResource() const {
    return mMostHitResource;
}
