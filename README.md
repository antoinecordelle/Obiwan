# About

Obiwan is a console program written in C++ to parse and deliver alerting and statistics on a csv http log file, as part
of a project proposed by Datadog.

![preview](https://github.com/antoinecordelle/Obiwan/blob/master/Obiwan.png)

# Table of contents

* [Setup](#Setup)
  * [Requirements](#Requirements)
  * [Installation](#install)
  * [Run](#run)
  * [Documentation](#documentation)
  * [Dependencies](#dependencies)
* [Architecture](#architecture)
  * [Overview](#overview)
  * [Structure](#structure)
  * [File Structure](#file-structure)
* [Possible improvements](#possible-improvements)


# Setup

## Requirements :

The program requires :

 At least **C++17**

- **CMake** to manage the build proces
- **Ncurses** to manage the user interface (Dashboard) 
- **Google Test** 
- **Doxygen** to generate the documentation

The program has been tested on both Linux and MacOS. It will not work with Windows as Ncurses is a Unix type library, that Windows does not support. If that does raise any issue, I am at your disposal to find a solution.

## Installation :

### Libs installation  :

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

## Overview

### Global architecture

### Lib choices

**Curses** is the console interface library used for most of the console programs used in Unix systems like htop or vim. 
To build a console interface, using ncurses was the logical choice and a quite interesting C library to use.

**GoogleTest** is one of the main C++ test libraries (with QTest and Boost Test)

**Doxygen** allows to generate a complete documentation from a templated header commenting. 
Therefore, most of the comments are located in the headers, allowing more readable source files.

## Structure



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

# Possible Improvements

### Processing improvements :


### Dashboard specific improvements :




















