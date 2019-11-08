#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>

class Utility {
public:
    Utility();
    static std::string removeChar(std::string& str, char charToRemove);
};


#endif //UTILITY_HPP
