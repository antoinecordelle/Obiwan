#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../ArgsParser/argsParser.hpp"
#include "../StatProcessor/statProcessor.hpp"
#include "../Metric/metric.hpp"
#include "../AlertHandler/alertHandler.hpp"
#include "../Dashboard/dashboard.hpp"

#include <string>
#include <vector>
#include <thread>

class Application
{
public:
    explicit Application(const Arguments& arguments);

    void run();

private:
    void launchDashboardThread();
    void stopDashboardThread();
    void processLogFile(std::tuple<HttpPacket, bool> initPacket);
    void processStats(const HttpPacket &packet);
    void processAlerts(const HttpPacket& packet);
    void processLastMetric();

private:
    std::string             mFilePath;
    Parser                  mParser;
    StatProcessor           mStatProcessor;
    AlertHandler            mAlertHandler;

    std::thread             mDashboardThread;
    Dashboard               mDashboard;

};

#endif // APPLICATION_HPP
