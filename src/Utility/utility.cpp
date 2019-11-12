#include <ctime>
#include "utility.hpp"


using namespace std;

string Utility::removeChar(string& str, char charToRemove) {
    str.erase(remove(str.begin(), str.end(), charToRemove), str.end() );
    return str;
}

HttpPacket &Utility::getHttpPacket(std::tuple<HttpPacket, bool>& packet) {
    return std::get<0>(packet);
}

bool Utility::isOver(std::tuple<HttpPacket, bool>& packet) {
    return std::get<1>(packet);
}

string Utility::getResource(const HttpPacket &httpPacket) {
    string request(httpPacket.request);
    int begin(request.find('/'));
    int end(min(request.find('/', begin + 1), request.find(' ', begin + 1)));
    return request.substr(begin, end - begin);
}

WINDOW* Utility::initializationBaseWindow(int height, int width, int startY, int startX, const std::string &text, bool center, bool withBox, bool title) {
    // Tool method to initialize windows
    WINDOW* win;
    win = newwin(height, width, startY, startX);
    if(withBox) {
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

std::string Utility::formatTime(const time_t *time, bool includeDate) {
    const char *format(includeDate ? "%d.%m.%Y %H:%M:%S"
                                   : "%H:%M:%S");
    std::tm* ptm = std::localtime(time);
    char buffer[32];
    std::strftime(buffer, 32, format, ptm);
    return buffer;
}
