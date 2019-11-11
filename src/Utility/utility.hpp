#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include "../Parser/parser.hpp"


class Utility {
public:
    static std::string removeChar(std::string& str, char charToRemove);

    static HttpPacket& getHttpPacket(std::tuple<HttpPacket, bool>& packet);
    static bool isOver(std::tuple<HttpPacket, bool>& packet);
};


#endif //UTILITY_HPP
