#include "application.hpp"

#include <iostream>
#include <cstdlib>

using namespace std;

Application::Application(const Arguments& arguments)
: mFilePath(arguments.filePath)
, mProcessor(arguments.filePath, arguments.threshold)
{

}

void Application::run()
{
    mProcessor.run();
}


