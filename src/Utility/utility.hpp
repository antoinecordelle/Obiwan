#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <algorithm>
#include <ncurses.h>
#include <sstream>
#include <map>
#include <memory>
#include "../Parser/parser.hpp"


/// Static utility class to ease the int and string user input through ncurses
class Utility {
public:
    /// Alias defining a safe overload of ncurses WINDOW pointer, the int(*)(WINDOW*) will call the WINDOW destructor delwin
    using WindowPtr = std::unique_ptr<WINDOW, int(*)(WINDOW*)>;

public:
    /// Utility function to remove every iteration of a character in a string
    static std::string              removeChar(std::string& str, char charToRemove);

    /// Utility function returning the HttpPacket from the parameter tuple. Used for readability
    static HttpPacket&              getHttpPacket(std::tuple<HttpPacket, bool>& packet);
    /// Utility function returning the isOver boolean from the parameter tuple. Used for readability
    static bool                     isOver(std::tuple<HttpPacket, bool>& packet);

    static std::string              getResource(const HttpPacket& httpPacket);

    /// Compares pair depending on the Value
    template <class Key, class Value>
    static bool                     keyMapCompare(std::pair<Key, Value> a, std::pair<Key, Value> b);

    /// Finds the max Value of a map<Key, Value>
    template <class Key, class Value>
    static std::pair<Key, Value>    findMaxValue(const std::map<Key, Value> &map);

    /// Tool method to initialize a window easily
    static WindowPtr                initializationBaseWindow(int height, int width, int startY, int startX, const std::string &text, bool center = false, bool withBox = true, bool title = false);

    static std::string              formatTime(const time_t *time, bool includeDate = true);
};

// Template functions have to be defined in the header and can't be defined in the cpp file.
template<class Key, class Value>
bool Utility::keyMapCompare(std::pair<Key, Value> a, std::pair<Key, Value> b) {
    return a.second < b.second;
}

template<class Key, class Value>
std::pair<Key, Value> Utility::findMaxValue(const std::map<Key, Value> &map) {
    if (!map.empty())
        return *std::max_element(map.begin(), map.end(), keyMapCompare<Key, Value>);
    return std::pair<Key, Value>();
}

#endif //UTILITY_HPP
