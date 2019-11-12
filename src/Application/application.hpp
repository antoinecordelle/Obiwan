#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../ArgsParser/argsParser.hpp"
#include "../StatProcessor/statProcessor.hpp"
#include "../Metrics/metrics.hpp"
#include "../AlertHandler/alertHandler.hpp"

#include <string>
#include <vector>

class Application
{
public:
    explicit Application(const Arguments& arguments);

    void            run();

private:
    void processLogFile(std::tuple<HttpPacket, bool> initPacket);
    void processStats(const HttpPacket &packet);
    void processAlerts(const HttpPacket& packet);
    void processLastMetric();

private:
    std::string             mFilePath;
    Parser                  mParser;
    StatProcessor           mStatProcessor;
    AlertHandler            mAlertHandler;
    std::vector<Metric>     mMetrics;
    std::vector<Alert>      mAlerts;
};

#endif // APPLICATION_HPP
