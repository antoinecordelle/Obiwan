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
    tuple<HttpPacket, bool> initPacket = mParser.parseOneLine();
    mStatProcessor.initialize(Utility::getHttpPacket(initPacket));
    mAlertHandler.initialize(Utility::getHttpPacket(initPacket));

    // Processing
    processLogFile(initPacket);
}

void Application::launchDashboardThread() {
    // Launch the dashboard main menu in its thread
    mDashboard.setRunning();
    mDashboardThread = thread(&Dashboard::run, &mDashboard);
}

void Application::processLogFile(tuple<HttpPacket, bool> packet) {
    // For every line, we check if the last tuple received has an isOver packet positive to state the end of the file
    // If not, we process the packet received in the statProcessor and the alertHandler, and parse the next line
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
