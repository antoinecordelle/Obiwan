#include "application.hpp"
#include "../Utility/utility.hpp"

#include <iostream>

using namespace std;

Application::Application(const Arguments& arguments)
: mFilePath(arguments.filePath)
, mParser(arguments.filePath)
, mStatProcessor(10)
, mAlertHandler(120, arguments.threshold)
{
}

void Application::run()
{
    tuple<HttpPacket, bool> InitPacket = mParser.parseOneLine();
    mStatProcessor.initialize(Utility::getHttpPacket(InitPacket));
    processLogFile(InitPacket);

    cout << mMetrics.size() << endl;
}

void Application::processLogFile(tuple<HttpPacket, bool> packet) {
    while (!Utility::isOver(packet))
    {
        processStats(Utility::getHttpPacket(packet));
        processAlerts(Utility::getHttpPacket(packet));

        // Transmit to front

        packet = mParser.parseOneLine();
    }
    processLastMetric();
}


void Application::processStats(const HttpPacket& packet) {
    if(mStatProcessor.processLine(packet))
    {
        vector<Metric> newMetrics = mStatProcessor.getMetrics();
        mMetrics.insert(mMetrics.end(), newMetrics.begin(), newMetrics.end());
        for (Metric m : newMetrics)
        {
            cout << m.getStartTime() << "   " << m.getCounter() << "  " << m.getMostHitResource().first << " "  <<
            m.getMostHitResource().second << endl;
        }
    }
}

void Application::processAlerts(const HttpPacket& packet) {
    if(mAlertHandler.processLine(packet))
    {
        mAlerts.push_back(mAlertHandler.getAlert(packet));
        cout << "Alert : " << mAlerts[mAlerts.size() - 1].triggerTime << "   " << mAlerts[mAlerts.size() - 1].hitCount
             << "   " << mAlerts[mAlerts.size() - 1].isPositive << endl;
    }
}

void Application::processLastMetric() {
    mMetrics.push_back(mStatProcessor.getLastMetric());
    auto m = mMetrics.back();
    cout << m.getStartTime() << "   " << m.getCounter() << "  " << m.getMostHitResource().first << " "  <<
         m.getMostHitResource().second << endl;
}
