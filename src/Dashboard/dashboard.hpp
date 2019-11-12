#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <vector>
#include <ncurses.h>
#include <sstream>
#include <mutex>
#include <atomic>
#include "../Metric/metric.hpp"
#include "../AlertHandler/alertHandler.hpp"
#include "../ArgsParser/argsParser.hpp"

class Dashboard {
public:
    using MetricVectorIte = std::vector<Metric>::iterator;

public:
    explicit Dashboard(const Arguments &arguments);

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
    void displayOneAlert(WINDOW* alertDisplay, const Alert &alert, int position);

    template <class Key, class Value>
    int displayMap(WINDOW* window, int position, const std::string &title, const std::map<Key, Value> &map);

private:
    std::string             mFileName;
    int                     mThreshold;
    int                     mStatFrame;
    int                     mAlertFrame;
    std::vector<Metric>     mMetrics;
    int                     mMetricsCount;
    std::vector<Alert>      mAlerts;
    int                     mFocusedMetricIndex;
    int                     mCurrentPage;
    int                     mPageSize;
    int                     mPageCount;
    std::atomic<bool>       mIsRunning;
    std::atomic<bool>       shouldRefreshAlerts;
    std::atomic<bool>       shouldRefreshMetrics;

    std::mutex mAlertLock;
    std::mutex mMetricLock;
};


template<class Key, class Value>
int Dashboard::displayMap(WINDOW* window, int position, const std::string &title, const std::map<Key, Value> &map)
{
    mvwprintw(window, position, 1, title.c_str());
    mvwprintw(window, position++, 13, "| hits");
    for (auto ite : map)
    {
        std::stringstream firstStr, secondStr;
        firstStr << ite.first;
        secondStr << ite.second;
        mvwprintw(window, position, 1, (firstStr.str()).c_str());
        mvwprintw(window, position++, 15, secondStr.str().c_str());
    }
    return position;
}

#endif //DASHBOARD_HPP
