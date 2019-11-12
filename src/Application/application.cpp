#include "application.hpp"
#include "../Utility/utility.hpp"

using namespace std;

Application::Application(const Arguments& arguments)
:mFilePath(arguments.filePath)
,mParser(arguments.filePath)
,mStatProcessor(arguments.statFrame)
,mAlertHandler(arguments.alertFrame, arguments.threshold)
,mDashboard(arguments)
{
}

void Application::run() {
    // Initialization
    launchDashboardThread();
    tuple<HttpPacket, bool> InitPacket = mParser.parseOneLine();
    mStatProcessor.initialize(Utility::getHttpPacket(InitPacket));

    processLogFile(InitPacket);
}

void Application::launchDashboardThread() {
    // Launch the dashboard main menu in its thread
    mDashboard.setRunning();
    mDashboardThread = thread(&Dashboard::run, &mDashboard);
}

void Application::processLogFile(tuple<HttpPacket, bool> packet) {
    while (!Utility::isOver(packet) && mDashboard.isRunning()) {
        processStats(Utility::getHttpPacket(packet));
        processAlerts(Utility::getHttpPacket(packet));
        packet = mParser.parseOneLine();
    }
    processLastMetric();
    mDashboardThread.join();
}


void Application::processStats(const HttpPacket& packet) {
    if(mStatProcessor.processLine(packet)) {
        vector<Metric> newMetrics(mStatProcessor.getMetrics());
        mDashboard.addMetrics(newMetrics);
    }
}

void Application::processAlerts(const HttpPacket& packet) {
    if(mAlertHandler.processLine(packet)) {
        Alert newAlert(mAlertHandler.getAlert(packet));
        mDashboard.addAlert(newAlert);
    }
}

void Application::processLastMetric() {
    Metric newMetric(mStatProcessor.getLastMetric());
    mDashboard.addMetrics(newMetric);
}
