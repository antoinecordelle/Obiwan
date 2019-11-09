#ifndef METRICS_HPP
#define METRICS_HPP

#include <ctime>
#include "../Parser/parser.hpp"

class Metric {
public:
    Metric() = default;
    explicit    Metric(time_t time);

    void        updateMetric(const HttpPacket& packet);
    void        computeMetric();
    time_t      getStartTime();
    int         getCounter() const;

private:
    int         mCounter;
    time_t      mStartTime;
};

#endif //METRICS_HPP
