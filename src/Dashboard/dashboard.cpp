#include "dashboard.hpp"

using namespace std;

Dashboard::Dashboard()
:mIsRunning(true)
{

}

void Dashboard::run()
{
    WINDOW* header;
    WINDOW* footer;
    WINDOW* metricsList;
    WINDOW* metricDetail;
    WINDOW* alertDisplay;

    mFocusedMetric = mMetrics.begin();
    initscr();
    curs_set(0);
    clear();
    refresh();
    noecho();
    keypad(stdscr, TRUE);
    header = initializationBaseWindow(1, COLS, 0, 0, "Logs from (insert file). Metrics every (insert sec) second.", true, false, true);
    footer = initializationBaseWindow(1, COLS, LINES - 1, 0, "Press F1 to leave. Press the up and down arrows to navigate through metrics", false, false, false);
    metricsList = initializationBaseWindow(3*LINES/5 - 1, 3*COLS/4, 1, 0, "Metrics list :", false, false, false);
    metricDetail = initializationBaseWindow(3*LINES/5 - 1, COLS/4, 1, 3*COLS/4 + 1, "Metric details :", false, true, true);
    alertDisplay = initializationBaseWindow(2*LINES/5, COLS, 3*LINES/5, 0, "Alerts (metrics from last 120s) : ", false, true, true);
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
                changeFocusedMetric(true);
                break;
            case KEY_DOWN:
                // Update the focused metric if Down is pressed
                changeFocusedMetric(true);
                break;
            default:
                break;
        }
    }

    delwin(header);
    delwin(footer);
    delwin(metricsList);
    delwin(metricDetail);
    delwin(alertDisplay);
    endwin();
}

WINDOW* Dashboard::initializationBaseWindow(int height, int width, int startY, int startX, std::string text, bool center, bool withBox, bool title)
{
    // Tool method to initialize windows
    WINDOW* win;
    win = newwin(height, width, startY, startX);
    if(withBox)
    {
        box(win, 0 , 0);
        if(title)
            mvwprintw(win, 0, 1, text.c_str());
        else if(!center)
            mvwprintw(win, 1, 1, text.c_str());
        else
            mvwprintw(win, 1, max(COLS/2 - 6, 0), text.c_str());
    }
    else
        mvwprintw(win, 0, 0, text.c_str());
    wrefresh(win);
    return win;
}


void Dashboard::addMetrics(std::vector<Metric> newMetricVector) {
    mMetrics.insert(mMetrics.end(), newMetricVector.begin(), newMetricVector.end());
}

void Dashboard::addMetrics(Metric metric) {
    mMetrics.push_back(metric);
}

void Dashboard::addAlert(Alert alert) {
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
        if(mFocusedMetric != mMetrics.begin())
            mFocusedMetric--;
    }
    else
    if(++mFocusedMetric == mMetrics.end())
        mFocusedMetric--;
}

