cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 17)

project(Obiwan)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(doc)

enable_testing ()
add_test (NAME Test
        COMMAND test)
