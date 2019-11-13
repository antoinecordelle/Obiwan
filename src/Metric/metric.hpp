#ifndef METRICS_HPP
#define METRICS_HPP

#include <ctime>
#include <string>
#include <map>
#include "../Parser/parser.hpp"

/// Class used to store and compute statistics for a timeWindow(10s by default)
class Metric {
public:
    Metric() = default;
    explicit    Metric(time_t time);

    /// Increments the metric's data with the new http packet parsed
    void        updateMetric(const HttpPacket& packet);

    /// Computes data when the timeWindow is finished and the metrics stores all the needed information
    void        computeMetric();
    time_t      getStartTime();
    int         getCounter() const;

    /// Returns the resource ( "/api" for instance) with the most hits in the resourceHits map
    const std::pair<std::string, int>   &getMostHitResource() const;
    const std::map<std::string, int>    &getResourceHits() const;
    const std::map<int, int>            &getResponseStatus() const;

private:
    int                                     mCounter;
    time_t                                  mStartTime;
    std::map<std::string, int>              mResourceHits;
    std::map<int, int>                      mResponseStatus;
    std::pair<std::string, int>             mMostHitResource;
};

#endif //METRICS_HPP
