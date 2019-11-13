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

/// Console user interface using the ncurses library
class Dashboard {
public:
    using MetricVectorIte = std::vector<Metric>::iterator;
    /// Alias defining a safe overload of ncurses WINDOW pointer, the int(*)(WINDOW*) will call the WINDOW destructor delwin
    using WindowPtr = std::unique_ptr<WINDOW, int(*)(WINDOW*)>;

public:
    explicit Dashboard(const Arguments &arguments);

    /// Method run : runs to display the interface, alerts, details and user interaction
    void run();
    bool isRunning();
    void setRunning();

    /// Adds to the stored metrics new metrics and will request a refresh of the metric Windows
    void addMetrics(std::vector<Metric> newMetricVector);
    /// Adds to the stored metrics a new metric and will request a refresh of the metric Windows
    void addMetrics(const Metric &newMetric);

    /// Adds to the stored alerts and will request a refresh of the alert Window
    void addAlert(Alert alert);

private:
    /// Displays a page of metrics, depending on the current page and the page size
    void displayMetrics(WindowPtr &metricList);
    /// Displays one metric in the list of metrics. Called by displayMetrics
    void displayOneMetric(WindowPtr &metricList, unsigned int position);
    /// Displays the details of the selected metric
    void displayDetails(WindowPtr  &metricDetail);

    /// Displays the alerts triggered in the alertDisplay window
    void displayAlerts(WindowPtr &alertDisplay);
    /// Displays one alert in the alert window. Called by displayAlerts
    void displayOneAlert(WindowPtr &alertDisplay, const Alert &alert, int position);

    void handleInput();
    /// Changes the focused metric displayed by displayDetails. Called by handleInput (up and down arrows)
    void changeFocusedMetric(bool next);
    /// Changes the page displayed on the metricList Window. Called by handleInput (left and right arrows)
    void navigatePages(bool next);

    /// Displays the map in the parameter window. Used in the metricDetail window for resources and status maps.
    template <class Key, class Value>
    int displayMap(WINDOW* window, int position, const std::string &title, const std::map<Key, Value> &map);

private:
    std::string             mFileName;
    int                     mThreshold;
    int                     mStatFrame;
    int                     mAlertFrame;
    /// List of metrics sent by Application
    std::vector<Metric>     mMetrics;
    /// Number of metrics stored, used to compute the number of pages
    int                     mMetricsCount;
    /// List of alerts sent by Application
    std::vector<Alert>      mAlerts;
    /// Index of the focused metric displayed in the metricDetail window
    int                     mFocusedMetricIndex;
    /// Current page displayed by the window metricList
    int                     mCurrentPage;
    /// Number of elements that can be displayed at once in the window metricList, depends on the size of the terminal
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
