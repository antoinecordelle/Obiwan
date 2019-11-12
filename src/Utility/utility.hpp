#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <algorithm>
#include <unordered_map>
#include "../Parser/parser.hpp"
#include <ncurses.h>


class Utility {
public:
    static std::string removeChar(std::string& str, char charToRemove);

    static HttpPacket& getHttpPacket(std::tuple<HttpPacket, bool>& packet);
    static bool isOver(std::tuple<HttpPacket, bool>& packet);

    static std::string getResource(const HttpPacket& httpPacket);

    template <class Key, class Value>
    static bool keyMapCompare(std::pair<Key, Value> a, std::pair<Key, Value> b);

    template <class Key, class Value>
    static std::pair<Key, Value> findMaxValue(const std::unordered_map<Key, Value> &map);

    static WINDOW* initializationBaseWindow(int height, int width, int startY, int startX, const std::string &text, bool center = false, bool withBox = true, bool title = false);
};

// Template functions have to be defined in the header and can't be defined in the cpp file.
template<class Key, class Value>
bool Utility::keyMapCompare(std::pair<Key, Value> a, std::pair<Key, Value> b) {
    return a.second < b.second;
}

template<class Key, class Value>
std::pair<Key, Value> Utility::findMaxValue(const std::unordered_map<Key, Value> &map) {
    if (!map.empty())
        return *std::max_element(map.begin(), map.end(), keyMapCompare<Key, Value>);
    else
        return std::pair<Key, Value>();
}

#endif //UTILITY_HPP
