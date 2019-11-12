#ifndef METRICS_HPP
#define METRICS_HPP

#include <ctime>
#include <string>
#include <unordered_map>
#include "../Parser/parser.hpp"

class Metric {
public:
    Metric() = default;
    explicit    Metric(time_t time);

    void        updateMetric(const HttpPacket& packet);
    void        computeMetric();
    time_t      getStartTime();
    int         getCounter() const;
    std::pair<std::string, int> getMostHitResource() const;

private:
    int                                     mCounter;
    time_t                                  mStartTime;
    std::unordered_map<std::string, int>    mResourceHits;
    std::pair<std::string, int>             mMostHitResource;
public:
};

#endif //METRICS_HPP
