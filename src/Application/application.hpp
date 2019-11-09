#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../ArgsParser/argsParser.hpp"
#include "../StatProcessor/statProcessor.hpp"
#include "../Metrics/metrics.hpp"

#include <string>
#include <vector>

class Application
{
public:
    explicit Application(const Arguments& arguments);

    void            run();

private:
    void processLogFile(std::tuple<HttpPacket, bool> initPacket);
    void processLine(const HttpPacket &packet);
    void generateAlerts(const HttpPacket& packet);
    void processLastMetric();

private:
    std::string             mFilePath;
    Parser                  mParser;
    StatProcessor           mStatProcessor;
    std::vector<Metric>    mMetrics;

};

#endif // APPLICATION_HPP
