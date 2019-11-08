#ifndef LOGERROREXCEPTION_HPP
#define LOGERROREXCEPTION_HPP

#include <exception>
#include <string>
#include <iostream>

class LogErrorException : public std::exception
{
public:
    const char* what() const throw()
    {
        return ("Invalid parsing of log line").c_str();
    }
};


#endif //LOGERROREXCEPTION_HPP
