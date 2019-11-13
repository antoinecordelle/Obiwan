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

/// Class managing the parser, the data processors (AlertHandler and StatProcessor)
/// and interface launch, and the link between the three parts
/**
 * @brief Runs the Dashboard, the Parser and processors (AlertHandler and StatProcessor), linking the three parts
 */
class Application
{
public:
    /// Constructor taking as arguments the parameters entered in the CLI
    explicit Application(const Arguments& arguments);

    /// Run : launch the interface's thread, initializes the processors and launch the logProcessing
    void run();

private:
    /// Launches the thread where the dashboard is running. Launched Dashboard::run
    void launchDashboardThread();

    /// Launches the processing of the whole log file. Parses every line and sends it to the StatProcessor (metric)
    /// and AlertHandler (alerting)
    /**
     * @param initPacket : first packet used to initialize the parsing. The bool part of the tuple is used to know if
     * this was the last line of the file
     */
    void processLogFile(std::tuple<HttpPacket, bool> initPacket);

    /// Sends the last parsed line to be processed by the StatProcessor. If a metric is generated, it will be sent to the
    /// dashboard. Called by processLogFile
    void processStats(const HttpPacket &packet);

    /// Sends the last parsed line to be processed by the AlertHandler. If an alert is generated, it will be sent to the
    /// dashboard. Called by processLogFile
    void processAlerts(const HttpPacket& packet);

    /// Sends the last metric of the file to the Dashboard
    void processLastMetric();

private:
    std::string             mFilePath;

    // Processing part
    Parser                  mParser;
    StatProcessor           mStatProcessor;
    AlertHandler            mAlertHandler;

    // Front part
    std::thread             mDashboardThread;
    Dashboard               mDashboard;

};

#endif // APPLICATION_HPP
