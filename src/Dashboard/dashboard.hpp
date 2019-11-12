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
    Dashboard(const std::string &fileName, int threshold);

    void run();
    bool isRunning();
    void setRunning();

    void changeFocusedMetric(bool next);
    void navigatePages(bool next);


    void addMetrics(std::vector<Metric> newMetricVector);
    void addMetrics(const Metric &newMetric);

    void addAlert(Alert alert);

private:
    void displayMetrics(WINDOW *metricList);
    void displayOneMetric(WINDOW *metricList, unsigned int position);
    void displayDetails(WINDOW *metricDetail);
    void displayAlerts(WINDOW *alertDisplay);

private:
    std::string             mFileName;
    int                     mThreshold;
    std::vector<Metric>     mMetrics;
    int                     mMetricsCount;
    std::vector<Alert>      mAlerts;
    int                     mFocusedMetricIndex;
    int                     mCurrentPage;
    int                     mPageSize;
    int                     mPageCount;
    bool                    mIsRunning;
    bool                    shouldRefresh;
};


#endif //DASHBOARD_HPP
