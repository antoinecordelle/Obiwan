#include "alertHandler.hpp"

Alert::Alert(time_t time, int count, bool positive)
:triggerTime(time)
,hitCount(count)
,isPositive(positive)
{

}

AlertHandler::AlertHandler(int timeWindow)
:isAlertTriggered(false)
,mCurrentCount(0)
,mTimeWindow(timeWindow)
{
}

void AlertHandler::initialize(const HttpPacket &httpPacket) {
    addPacket(httpPacket);
}

bool AlertHandler::processLine(const HttpPacket &httpPacket) {
    addPacket(httpPacket);

    removeOldPackets(httpPacket);
}

void AlertHandler::getAlert() {

}

void AlertHandler::addPacket(const HttpPacket &httpPacket)
{
    mPacketList.push_back(httpPacket);
    mCurrentCount++;
}

void AlertHandler::removeOldPackets(const HttpPacket &httpPacket) {
    time_t currentTime(httpPacket.date);
    int toDestroy(0);
    ListIterator iterator(mPacketList.begin());
    while (iterator->date + mTimeWindow < currentTime)
    {
        mCurrentCount--;
    }
    mPacketList.erase(mPacketList.begin(), iterator);
}

