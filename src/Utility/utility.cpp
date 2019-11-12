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
