# About

Obiwan is a console program written in C++ to parse and deliver alerting and statistics on a csv http log file, as part
of a project proposed by Datadog.

The program will process alerts and metrics as it streams the log file, displaying them in the dashboard.

![preview](https://github.com/antoinecordelle/Obiwan/blob/master/screenshot.png)

# Table of contents

* [Setup](#Setup)
  * [Requirements](#Requirements)
  * [Installation](#installation)
  * [Run](#run)
  * [Documentation](#documentation)
  * [Dependencies](#dependencies)
* [Architecture](#architecture)
  * [Global Architecture](#global-architecture)
  * [File Structure](#file-structure)
  * [Efficiency](#efficiency)
* [Possible improvements](#possible-improvements)


# Setup

## Requirements

The program requires :
- **C++17**
- **CMake** to manage the build proces
- **Ncurses** to manage the user interface (Dashboard) 
- **Google Test** 
- **Doxygen** to generate the documentation

The program has been tested on both Linux and MacOS. It will not work with Windows as Ncurses is a Unix type library, that Windows does not support. If that does raise any issue, I am at your disposal to find a solution.

## Installation

### Libs installation 

**Libs for Linux**
```
apt install cmake
apt install libncurses-dev
apt install doxygen   # to generate doc
```

**Libs for MacOS**
```
brew install cmake
brew install ncurses
brew install doxygen   # to generate doc
```

**Google Test Installation**
```
git clone https://github.com/google/googletest
cd googletest
mkdir build
cd build
cmake ..
make
make install
```

### Project building (both MacOS and Linux)
```
cd (project)
mkdir build
cd build
cmake ..
make
```

If you encounter any issue while installing, I am at your disposal to find the solution.

## Run

To run tests for the alert logic : 
In the (project)/build folder : 
``` ./test/runTests```

To run the program :
In the (project)/build folder : 
```./src/app -f filePath.txt``` 

Parameters :<br>
- ```-f / --filePath filePath.txt``` : path of the csv file to be parsed (required)
- ```-t / --threshold 10``` (default 10): integer to determine the alert threshold : number of request per second that will trigger an alert
- ```-s / --statFrame 10``` (default 10): integer to determine the time window of every metric computed in second
- ```-a / --alertFrame 120``` (default 120): integer to determine the time window watched by the alerting system
- ```-h ``` : help message on parameters and overview 
    
## Documentation

To generate the documentation :
Install doxygen : ```apt install doxygen``` or ```brew install doxygen```

Generation : in (project)/build : 
```
cmake ..
make doc
```

To access the documentation : Open ```(project)/build/doc/html/annotated.html```

Most of the documentation is located in the header files.


## Dependencies

This program uses : <br>
- Ncurses for the console interface : C library used in programs like htop or vim for instance

- Google Test : C++ test library

- Doxygen

# Architecture

The program will process alerts and metrics as it streams the log file, displaying them in the dashboard when they come up.

## Global architecture

The project is based around three main parts, everything being articulated by the center class Application. <br>

The different Processors (AlertHandler and StatProcessor) are independent and have the same input function names (used by Application),
making all the data processing parts really modular.

#### Application :
- Launches the different modules of the program
- Responsible of gathering the parsed data
- Distributes this data to the Processors (AlertHandler and StatProcessor)
- Sends the resulting metrics/alerts to the dashboard

#### Parser 
- Parses every line of the csv file
- Returns HttpPackets to the application that distributes those packets to the Processors

#### Processors
###### StatProcessor 
- Computes metrics for every window of 10 seconds (default value)
- Returns Metrics (aggregated data over those windows) to the Application class, that transmits them to the Dashboard

###### AlertHandler 
- Gets HttpPackets which are enqueued in a queue that holds 2 minutes of history. Older Packets are removed.
- Triggers alerts if the traffic logged is too high in the past 2 minutes (default value). 
- Triggers a recovery message if the traffic is going under this threshold after an alert was triggered.
- Returns Alerts to the Application that are sent to the Application class, that transmiss them to the Dashboard

#### Dashboard 
- Displays data sent by the Application : 
    * Metrics list : list of metrics over several pages
    * Metric details : details of the selected metrics (resources hit, status statistics, total hit count)
    * Alerts list

## Lib choices

**Curses** is the console interface library used for most of the console programs used in Unix systems like htop or vim. 
To build a console interface, using ncurses was the logical choice and a quite interesting C library to use.

**GoogleTest** is one of the main C++ test libraries (with QTest and Boost Test)

**Doxygen** allows to generate a complete documentation from a templated header commenting. 
Therefore, most of the comments are located in the headers, allowing more readable source files.

## File structure
```
. 
├── /src                    
│   ├─── /AlertHander       
│   ├─── /Application
│   ├─── /ArgsParser
│   ├─── /Dashboard
│   ├─── /Error
│   ├─── /Metric
│   ├─── /Parser
│   ├─── /StatProcessor
│   ├─── /Utility
│   ├─ CMakeLists.txt           
│   └─ main.cpp   
├── /doc  
│   ├─ CMakeLists.txt      
│   └─ Doxyfile.in
├── /test
│   ├─ CMakeLists.txt           
│   └─ test.cpp   
└─ CMakeLists.txt           
```

## Efficiency

The log file is read once, line by line, every line being processed by the Processors as it is parsed. This allow the program
to parse bigger files, as the file is not stored in the program memory and the program only keeps two minutes (by default) 
of HttpPacket history. <br>
The metrics and alerts are currently being displayed when they are delivered by the corresponding processing units,
and the Dashboard's thread being separated, it allows to navigate through metrics even when the file is still being processed.
Therefore, the program should be able to parse quite big files, the only downside is that the view is updated for every chunk of 
metrics computed, that could mean a lot of dashboard updates if we have a long time range and a few hits per window.

# Possible Improvements

### Processing improvements :

**Other metrics and alerts to add :** Some interesting metrics can be added, such as resources that trigger the most status errors, 
statistics on errors, on packages sizes. Other alerts can be added as well, for instance regarding 500 or 404 errors.

**Resiliency to badly formatted files :** Csv that are not in the awaited format will result in a crash, adding errors on this
and resiliency if some lines are not conventional can be interesting.

**Unit testing :** Currently, only the AlertLogic and the Metrics Processing are tested by GoogleTest. On the long run, a more systematic unit testing would be a good investment, allowing the project to be more maintainable.

**Export solution :** Adding the possibility to export the analysis could be a valuable feature.

**Allow live streaming of logs :** Being able to live stream requests/logs that are hitting the server could be the base of 
a live monitoring system instead of only being able to analyse the logs afterwards.

### Dashboard specific improvements :

**Better responsivity :** The dashboard's responsivity is not ideal, especially when setting the console size to a way smaller window.

**Show the evolution of the metrics :** Being able to monitor the evolution of the metrics, with graphs showing the evolution of the traffic,
of the resource load and the status can be valuable insights.


















