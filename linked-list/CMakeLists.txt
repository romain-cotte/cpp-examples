cmake_minimum_required (VERSION 2.6)
project (Linked-list)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# add the executable
add_executable(linked-list linked-list.cpp)
