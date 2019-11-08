#include "utility.hpp"
#include <algorithm>

using namespace std;

void Utility::removeChar(string& str, char charToRemove) {
    str.erase(remove(str.begin(), str.end(), charToRemove), str.end() );
}
