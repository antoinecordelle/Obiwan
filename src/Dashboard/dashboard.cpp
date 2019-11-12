#include "dashboard.hpp"
#include "../Utility/utility.hpp"

using namespace std;

Dashboard::Dashboard(const string &fileName, int threshold)
:mFileName(fileName)
,mThreshold(threshold)
,mMetricsCount(0)
,mFocusedMetricIndex(0)
,mCurrentPage(0)
,mPageSize(0)
,mPageCount(0)
,mIsRunning(true)
,shouldRefresh(false)
{
}

void Dashboard::run()
{
    WINDOW* header;
    WINDOW* footer;
    WINDOW* metricList;
    WINDOW* metricDetail;
    WINDOW* alertDisplay;

    initscr();
    curs_set(0);
    clear();
    refresh();
    noecho();
    keypad(stdscr, TRUE);
    mPageSize = 3*LINES/5 - 2;
    mPageCount = mMetricsCount/mPageSize + 1;

    string headerText = "Logs from " + mFileName +". Metrics every " + to_string(mThreshold) + " second.";
    string metricListText = "Metrics list p." + to_string(mCurrentPage + 1) + "/" + to_string(mPageCount) +
                             ": (next page : n, previous : p)";
    header = Utility::initializationBaseWindow(1, COLS, 0, 0, headerText, true, false, true);
    footer = Utility::initializationBaseWindow(1, COLS, LINES - 1, 0, "Press F1 to leave. Press the up and down arrows to navigate through metrics", false, false, false);
    metricList = Utility::initializationBaseWindow(3*LINES/5 - 1, 3*COLS/4, 1, 0, metricListText, false, false, false);
    metricDetail = Utility::initializationBaseWindow(3*LINES/5 - 1, COLS/4, 1, 3*COLS/4 + 1, "Metric details :", false, true, true);
    alertDisplay = Utility::initializationBaseWindow(2*LINES/5, COLS, 3*LINES/5, 0, "Alerts (metrics from last 120s) : ", false, true, true);
    int input;
    timeout(1000);
    while(isRunning())
    {
        input = getch();
        switch(input)
        {
            case KEY_F(1):
                // Exits the program if F1 is pressed
                mIsRunning = false;
                break;
            case KEY_UP:
                // Update the focused metric if Up is pressed
                shouldRefresh = true;
                changeFocusedMetric(false);
                break;
            case KEY_DOWN:
                // Update the focused metric if Down is pressed
                shouldRefresh = true;
                changeFocusedMetric(true);
                break;
            case KEY_RIGHT:
                // Update the next metric page if N is pressed
                shouldRefresh = true;
                navigatePages(false);
                break;
            case KEY_LEFT:
                // Update to the previous metric page if P is pressed
                shouldRefresh = true;
                navigatePages(true);
                break;
            default:
                break;
        }
        if(shouldRefresh)
        {
            shouldRefresh = false;
            displayMetrics(metricList);
            displayDetails(metricDetail);
            displayAlerts(alertDisplay);
        }
    }

    delwin(header);
    delwin(footer);
    delwin(metricList);
    delwin(metricDetail);
    delwin(alertDisplay);
    endwin();
}

void Dashboard::displayMetrics(WINDOW* metricList)
{
    wclear(metricList);
    string metricListText = "Metrics list p." + to_string(mCurrentPage + 1) + "/" + to_string(mPageCount) +
                            ": (next: left arrow, previous: right)";
    metricList = Utility::initializationBaseWindow(3*LINES/5 - 1, 3*COLS/4, 1, 0, metricListText, false, false, false);

    for (unsigned int i(0); i < mPageSize; i++)
    {
        displayOneMetric(metricList, i);
    }

    wrefresh(metricList);
}

void Dashboard::displayOneMetric(WINDOW* metricList, unsigned int position)
{
    unsigned int metricIndex(position + mPageSize*mCurrentPage);
    if (metricIndex < mMetrics.size())
    {
        int startingPos = 2;
        string text;
        Metric& metric = mMetrics[metricIndex];
        time_t metricTime = metric.getStartTime();
        auto mostHitResource = metric.getMostHitResource();
        if (metricIndex == mFocusedMetricIndex)
        {
            text += 'X';
            startingPos = 1;
        }
        text += Utility::formatTime(&metricTime);
        if (metric.getCounter() == 0)
        {
            text += ": No hit";
        }
        else
        {
            text += ": " + to_string(metric.getCounter()) + " hits"
                    + "  |  " + mostHitResource.first + " hit " + to_string(mostHitResource.second) + " times";
        }
        mvwprintw(metricList, position + 1, startingPos, text.c_str());
    }
}

void Dashboard::displayDetails(WINDOW* metricDetail)
{
    wclear(metricDetail);
    metricDetail = Utility::initializationBaseWindow(3*LINES/5 - 1, COLS/4, 1, 3*COLS/4 + 1, "Metric details :", false, true, true);

    wrefresh(metricDetail);
}

void Dashboard::displayAlerts(WINDOW* alertDisplay)
{
    wclear(alertDisplay);
    alertDisplay = Utility::initializationBaseWindow(2*LINES/5, COLS, 3*LINES/5, 0, "Alerts (metrics from last 120s) : ", false, true, true);
    int position(0);
    mAlerts.insert(mAlerts.end(), mAlerts.begin(), mAlerts.end());
    for(unsigned int i = mAlerts.size() - 1; i != -1; i--)
    {
        displayOneAlert(alertDisplay, mAlerts[i], position++);
    }
    wrefresh(alertDisplay);
}

void Dashboard::displayOneAlert(WINDOW* alertDisplay, Alert alert, int position)
{
    time_t alertTime(alert.triggerTime);

    mvwprintw(alertDisplay, position + 1, 1, Utility::formatTime(&alertTime).c_str());
    if(alert.isPositive)
    {
        mvwprintw(alertDisplay, position + 1, 20, (" :  High traffic generated : " + to_string(alert.hitCount) + " hits").c_str());
    }
    else
    {
        mvwprintw(alertDisplay, position + 1, 20, " :  Recovered from alert");
    }
}

void Dashboard::addMetrics(std::vector<Metric> newMetricVector) {
    shouldRefresh = true;
    mMetrics.insert(mMetrics.end(), newMetricVector.begin(), newMetricVector.end());
    mMetricsCount+= newMetricVector.size();
}

void Dashboard::addMetrics(const Metric &metric) {
    shouldRefresh = true;
    mMetrics.push_back(metric);
    mMetricsCount+= 1;
}

void Dashboard::addAlert(Alert alert) {
    shouldRefresh = true;
    mAlerts.push_back(alert);
}

bool Dashboard::isRunning()
{
    return mIsRunning;
}

void Dashboard::setRunning()
{
    mIsRunning = true;
}

void Dashboard::changeFocusedMetric(bool next)
{
    if(next)
    {
        if(mFocusedMetricIndex != mMetrics.size() - 1)
            mFocusedMetricIndex++;
    }
    else if(mFocusedMetricIndex != 0)
        mFocusedMetricIndex--;
}

void Dashboard::navigatePages(bool next) {
    if(next)
    {
        if(mCurrentPage != 0)
        {
            mCurrentPage--;
            if (mCurrentPage*mPageSize < mMetrics.size())
                mFocusedMetricIndex = mCurrentPage*mPageSize;
        }
    }
    else if(mCurrentPage != mPageCount - 1)
    {
        mCurrentPage++;
        if (mCurrentPage*mPageSize < mMetrics.size())
            mFocusedMetricIndex = mCurrentPage*mPageSize;
    }
}

