#include "application.hpp"

#include <iostream>
#include <cstdlib>

using namespace std;

Application::Application(const Arguments& arguments)
: mFilePath(arguments.filePath)
, mLogFile(arguments.filePath)
, mStatProcessor(&mLogFile)
{
}

void Application::run()
{
    mStatProcessor.run();
}
