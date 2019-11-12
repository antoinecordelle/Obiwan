#ifndef ALERTHANDLER_HPP
#define ALERTHANDLER_HPP

#include <queue>
#include "../Parser/parser.hpp"

struct Alert {
    time_t triggerTime;
    int hitCount;
    bool isPositive;

    Alert(time_t time, int count, bool positive);
};


class AlertHandler {
public:
    AlertHandler(int timeWindow, int threshold);

    void initialize(const HttpPacket &httpPacket);
    bool processLine(const HttpPacket &httpPacket);

    Alert getAlert(const HttpPacket &httpPacket);

private:
    void addPacket(const HttpPacket &httpPacket);
    void removeOldPackets(const HttpPacket &httpPacket);

private:
    std::queue<HttpPacket>   mPacketQueue;
    int                      mCurrentCount;
    time_t                   mCurrentTime;
    bool                     isAlertTriggered;
    int                      mTimeWindow;
    int                      mThreshold;
};


#endif //ALERTHANDLER_HPP
