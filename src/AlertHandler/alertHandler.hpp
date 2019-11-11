#ifndef ALERTHANDLER_HPP
#define ALERTHANDLER_HPP

#include <list>
#include "../Parser/parser.hpp"

struct Alert {
    time_t triggerTime;
    int hitCount;
    bool isPositive;

    Alert(time_t time, int count, bool positive);
};


class AlertHandler {
public:
    using ListIterator = std::list<HttpPacket>::iterator;

public:
    AlertHandler(int timeWindow);

    void initialize(const HttpPacket &httpPacket);
    bool processLine(const HttpPacket &httpPacket);

    void getAlert();

private:
    void addPacket(const HttpPacket &httpPacket);
    void removeOldPackets(const HttpPacket &httpPacket);

private:
    std::list<HttpPacket>   mPacketList;
    int                     mCurrentCount;
    bool                    isAlertTriggered;
    int                     mTimeWindow;

};


#endif //ALERTHANDLER_HPP
