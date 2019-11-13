#include "AlertHandler/alertHandler.hpp"
#include <gtest/gtest.h>
#include <StatProcessor/statProcessor.hpp>

using namespace std;

// Test Alert Logic
TEST ( TestAlertLogic, TriggerPositiveAlert)
{
    // Create an alert handler parsing a 5sec timeWindow, that triggers an alert when there are more than 5 hits
    // per second
    AlertHandler alertHandler(5, 5);
    HttpPacket packet;
    // Generate 24 packets in a 5 second time frame
    for (unsigned int i(0); i < 24; i++)
    {
        packet.date = i/5;
        if(alertHandler.processLine(packet))
            alertHandler.getAlert(packet);
    }

    // The 25th packet should not generate an alert
    packet.date = 4;
    EXPECT_EQ(false, alertHandler.processLine(packet));

    // The 26th packet should generate an alert, and the alert to be positive
    packet.date = 5;
    EXPECT_EQ(true, alertHandler.processLine(packet));
    EXPECT_EQ(true, alertHandler.getAlert(packet).isPositive);
}

TEST ( TestAlertLogic, TriggerRecoveryAlert)
{
    // Create an alert handler parsing a 5sec timeWindow, that triggers an alert when there are more than 5 hits
    // per second
    AlertHandler alertHandler(5, 5);
    HttpPacket packet;
    // Generate 24 packets in a 5 second time frame
    for (unsigned int i(0); i < 26; i++)
    {
        packet.date = i/5;
        if(alertHandler.processLine(packet))
            alertHandler.getAlert(packet);
    }

    // An alert a few seconds later with will reduce the number of hits in the last 5 minutes
    // and will trigger a negative alert, meaning a recovery
    packet.date = 10;
    EXPECT_EQ(true, alertHandler.processLine(packet));
    EXPECT_EQ(false, alertHandler.getAlert(packet).isPositive);
}

TEST ( MetricProcessingLogic, MetricProcessingLogic_GetMetric) {
    // Create a time processor processing data from the last 5 sec of logs
    StatProcessor statProcessor(5);
    // Generate 20 packets in a 5 second time frame
    HttpPacket packet;
    packet.date = 0;
    packet.status = 200;
    packet.request = "GET /api/test";
    statProcessor.initialize(packet);
    for (unsigned int i(0); i < 19; i++) {
        packet.date = i / 5;
        statProcessor.processLine(packet);
    }

    // A packet 4 seconds after the beginning of the parsing should not complete the metric
    packet.date = 4;
    EXPECT_EQ(false, statProcessor.processLine(packet));

    // A packet 5 seconds after the beginning of the parsing should complete the metric, with 20 elements
    // and no empty metric coming after
    packet.date = 5;
    EXPECT_EQ(true, statProcessor.processLine(packet));
    auto metrics = statProcessor.getMetrics();
    EXPECT_EQ(1, metrics.size());
    EXPECT_EQ(20, metrics[0].getCounter());
}

TEST ( MetricProcessingLogic, MetricProcessingLogic_GetEmptyMetrics) {
    // Create a time processor processing data from the last 5 sec of logs
    StatProcessor statProcessor(5);
    // Generate 20 packets in a 5 second time frame
    HttpPacket packet;
    packet.date = 0;
    packet.status = 200;
    packet.request = "GET /api/test";
    statProcessor.initialize(packet);
    for (unsigned int i(0); i < 20; i++) {
        packet.date = i / 5;
        statProcessor.processLine(packet);
    }

    // A packet 10 seconds after the beginning of the parsing should complete the metric
    // and return 2 empty metric after that
    packet.date = 15;
    EXPECT_EQ(true, statProcessor.processLine(packet));
    auto metrics = statProcessor.getMetrics();
    EXPECT_EQ(3, metrics.size());
}

int main(int argc,char *argv[]) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
