#include "utility.hpp"
#include <algorithm>

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
