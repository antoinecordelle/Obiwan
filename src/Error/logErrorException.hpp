#ifndef LOGERROREXCEPTION_HPP
#define LOGERROREXCEPTION_HPP

#include <exception>
#include <string>
#include <iostream>

class LogErrorException : public std::exception
{
public:
    [[nodiscard]] const char* what() const noexcept override
    {
        return "Invalid parsing of log line";
    }
};


#endif //LOGERROREXCEPTION_HPP
