#include "application.hpp"
#include "../Utility/utility.hpp"

using namespace std;

Application::Application(const Arguments& arguments)
: mFilePath(arguments.filePath)
, mParser(arguments.filePath)
, mStatProcessor(arguments.statFrame)
, mAlertHandler(arguments.alertFrame, arguments.threshold)
, mDashboard(arguments)
{
}

void Application::run()
{
    tuple<HttpPacket, bool> InitPacket = mParser.parseOneLine();
    mStatProcessor.initialize(Utility::getHttpPacket(InitPacket));
    processLogFile(InitPacket);
    mDashboard.run();
}

void Application::processLogFile(tuple<HttpPacket, bool> packet) {
    while (!Utility::isOver(packet))
    {
        processStats(Utility::getHttpPacket(packet));
        processAlerts(Utility::getHttpPacket(packet));
        packet = mParser.parseOneLine();
    }
    processLastMetric();
}


void Application::processStats(const HttpPacket& packet) {
    if(mStatProcessor.processLine(packet))
    {
        vector<Metric> newMetrics(mStatProcessor.getMetrics());
        mDashboard.addMetrics(newMetrics);
    }
}

void Application::processAlerts(const HttpPacket& packet) {
    if(mAlertHandler.processLine(packet))
    {
        Alert newAlert(mAlertHandler.getAlert(packet));
        mDashboard.addAlert(newAlert);
    }
}

void Application::processLastMetric() {
    Metric newMetric(mStatProcessor.getLastMetric());
    mDashboard.addMetrics(newMetric);
}
