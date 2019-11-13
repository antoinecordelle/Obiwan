#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <vector>
#include <sstream>
#include <mutex>
#include <atomic>
#include <ncurses.h>
#include <memory>
#include "../Metric/metric.hpp"
#include "../AlertHandler/alertHandler.hpp"
#include "../ArgsParser/argsParser.hpp"

class Dashboard {
public:
    using MetricVectorIte = std::vector<Metric>::iterator;
    using WindowPtr = std::unique_ptr<WINDOW, int(*)(WINDOW*)>;

public:
    explicit Dashboard(const Arguments &arguments);

    void run();
    bool isRunning();
    void setRunning();

    void addMetrics(std::vector<Metric> newMetricVector);
    void addMetrics(const Metric &newMetric);

    void addAlert(Alert alert);

private:
    void displayMetrics(WindowPtr &metricList);
    void displayOneMetric(WindowPtr &metricList, unsigned int position);
    void displayDetails(WindowPtr  &metricDetail);
    void displayAlerts(WindowPtr &alertDisplay);
    void displayOneAlert(WindowPtr &alertDisplay, const Alert &alert, int position);

    void handleInput();
    void changeFocusedMetric(bool next);
    void navigatePages(bool next);

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

    std::mutex              mAlertLock;
    std::mutex              mMetricLock;
};


template<class Key, class Value>
int Dashboard::displayMap(WINDOW* window, int position, const std::string &title, const std::map<Key, Value> &map) {
    mvwprintw(window, position, 1, title.c_str());
    mvwprintw(window, position++, 13, "| hits");
    for (auto ite : map) {
        std::stringstream firstStr, secondStr;
        firstStr << ite.first;
        secondStr << ite.second;
        mvwprintw(window, position, 1, (firstStr.str()).c_str());
        mvwprintw(window, position++, 15, secondStr.str().c_str());
    }
    return position;
}

#endif //DASHBOARD_HPP
