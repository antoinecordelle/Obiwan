#ifndef METRICS_HPP
#define METRICS_HPP

#include <ctime>
#include <string>
#include <map>
#include "../Parser/parser.hpp"

class Metric {
public:
    Metric() = default;
    explicit    Metric(time_t time);

    void        updateMetric(const HttpPacket& packet);
    void        computeMetric();
    time_t      getStartTime();
    int         getCounter() const;
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
