#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <string>
#include <list>
#include <vector>
#include "../Parser/parser.hpp"
#include "../Metric/metric.hpp"

/// Class managing the statistics processing of the logs
/**
 * @brief It will be sent packets from the application, will add the packet to the current metric, that will be sent to
 * Dashboard if the timeWindow has ended
 */
class StatProcessor {
public:
    using ListIterator = std::list<HttpPacket>::iterator;

public:
    explicit StatProcessor(int timeWindow);

    /// Initializes the StatProcessor with the first packet.
    void                initialize(const HttpPacket &httpPacket);

    /// Processes the last line received
    /**
     * @brief Updates the current metric with the new packet.
     * @return If we switch to a new timeWindow, returns true to indicate the Application to getMetrics
     */
    bool                processLine(const HttpPacket &httpPacket);

    /// Sends the most recent metrics
    /**
     * @brief Sends the currentMetrics and creates a new one with the newest packet (which is in a new timeWindow).
     * Will fill the vector with empty metrics if necessary
     */
    std::vector<Metric> getMetrics();
    /// Sends the last metric when the last line has been parsed.
    Metric              getLastMetric();

private:
    Metric     mCurrentMetric{};
    Metric     mBufferedMetric{};
    int        mTimeWindow;
};

#endif //PROCESSOR_HPP
