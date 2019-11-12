#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <vector>
#include <ncurses.h>
#include "../Metric/metric.hpp"
#include "../AlertHandler/alertHandler.hpp"

class Dashboard {
public:
    using MetricVectorIte = std::vector<Metric>::iterator;

public:
    Dashboard();

    void run();
    bool isRunning();
    void setRunning();

    WINDOW* initializationBaseWindow(int height, int width, int startY, int startX, std::string text, bool center = false, bool withBox = true, bool title = false);

    void changeFocusedMetric(bool next);


    void addMetrics(std::vector<Metric> newMetricVector);
    void addMetrics(Metric newMetric);

    void addAlert(Alert alert);

private:
    std::vector<Metric>     mMetrics;
    std::vector<Alert>      mAlerts;
    MetricVectorIte         mFocusedMetric;
    bool                    mIsRunning;
};


#endif //DASHBOARD_HPP
