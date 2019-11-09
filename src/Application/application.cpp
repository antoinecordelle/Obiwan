#include "application.hpp"

#include <iostream>
#include <cstdlib>

using namespace std;

Application::Application(const Arguments& arguments)
: mFilePath(arguments.filePath)
, mParser(arguments.filePath)
{
}

void Application::run()
{
    tuple<HttpPacket, bool> packet = mParser.parseOneLine();
    while (!std::get<1>(packet))
    {
        processLine(std::get<0>(packet));
        generateAlerts(std::get<0>(packet));
        // Transmit to front

        packet = mParser.parseOneLine();
    }
}

void Application::processLine(HttpPacket& packet) {
    vector<Metric> newMetrics = mStatProcessor.processLine(packet);
    mMetrics.insert(mMetrics.end(), newMetrics.begin(), newMetrics.end());
}

void Application::generateAlerts(HttpPacket& packet) {

}
