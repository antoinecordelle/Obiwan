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
    mResponseStatus[packet.status] += 1;
}

time_t Metric::getStartTime() {
    return mStartTime;
}

int Metric::getCounter() const {
    return mCounter;
}

const pair<std::string, int> & Metric::getMostHitResource() const {
    return mMostHitResource;
}

const unordered_map<std::string, int> &Metric::getResourceHits() const {
    return mResourceHits;
}

const unordered_map<int, int> &Metric::getResponseStatus() const {
    return mResponseStatus;
}
