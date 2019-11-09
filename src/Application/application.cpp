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
    tuple<HttpPacket, bool> InitPacket = mParser.parseOneLine();
    mStatProcessor.initialize(get<0>(InitPacket));
    processLogFile(InitPacket);

    int counter(0);
    cout << mMetrics.size() << endl;
    for(Metric m : mMetrics)
    {
        counter+= m.getCounter();
        cout << m.getStartTime() << "   " << m.getCounter() << endl;
    }
    cout << counter << endl;
}

void Application::processLogFile(tuple<HttpPacket, bool> packet) {
    while (!get<1>(packet))
    {
        processLine(get<0>(packet));
        generateAlerts(get<0>(packet));
        // Transmit to front

        packet = mParser.parseOneLine();
    }
    processLastMetric();
}


void Application::processLine(const HttpPacket& packet) {
    if(mStatProcessor.processLine(packet))
    {
        vector<Metric> newMetrics = mStatProcessor.getMetrics();
        mMetrics.insert(mMetrics.end(), newMetrics.begin(), newMetrics.end());
    }
}

void Application::generateAlerts(const HttpPacket& packet) {

}

void Application::processLastMetric() {
    mMetrics.push_back(mStatProcessor.getLastMetric());
}
