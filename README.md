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

### Libs for Linux :

**Libs installation**
```
apt install cmake
apt install ncurses
apt install doxygen   # to generate doc
```
**Google Test installation**
```
git clone https://github.com/google/googletest
cd googletest
mkdir build
cd build
cmake ..
make
make install
```

### Libs for MacOS

**Libs installation**
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
```./src/app```


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

This program uses :
Ncurses for the console interface : C library the one used in programs like htop or vim for instance

Google Test : C++ test library

Doxygen
