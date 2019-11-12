#include "alertHandler.hpp"

Alert::Alert(time_t time, int count, bool positive)
:triggerTime(time)
,hitCount(count)
,isPositive(positive)
{

}

AlertHandler::AlertHandler(int timeWindow, int threshold)
:isAlertTriggered(false)
,mCurrentCount(0)
,mTimeWindow(timeWindow)
,mThreshold(threshold*timeWindow)
{
}

void AlertHandler::initialize(const HttpPacket &httpPacket) {
    addPacket(httpPacket);
}

bool AlertHandler::processLine(const HttpPacket &httpPacket) {
    addPacket(httpPacket);
    removeOldPackets(httpPacket);
    // If an alert was already triggered and the count went under the threshold, trigger an alert to announce recovery
    // If no alert was triggered and the count went above the threshold, trigger an alert
    return (isAlertTriggered && mCurrentCount < mThreshold) ||
           (!isAlertTriggered && mCurrentCount >= mThreshold);
}

Alert AlertHandler::getAlert(const HttpPacket &httpPacket) {
    isAlertTriggered = !isAlertTriggered;
    return Alert(httpPacket.date, mCurrentCount, isAlertTriggered);
}

void AlertHandler::addPacket(const HttpPacket &httpPacket)
{
    mPacketQueue.push(httpPacket);
    mCurrentCount++;
}

void AlertHandler::removeOldPackets(const HttpPacket &httpPacket) {
    time_t currentTime(httpPacket.date);
    while (mPacketQueue.front().date + mTimeWindow < currentTime)
    {
        mCurrentCount--;
        mPacketQueue.pop();
    }
}
