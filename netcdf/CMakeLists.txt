cmake_minimum_required(VERSION 3.16)

project(NetcdfReader VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO 8: Use configure_file to configure and copy TutorialConfig.h.in to
#         TutorialConfig.h
# configure_file(TutorialConfig.h.in TutorialConfig.h)

# TODO 3: Add an executable called Tutorial to the project
# Hint: Be sure to specify the source file as tutorial.cxx
add_executable(netcdf_reader main.cpp)

# TODO 9: Use target_include_directories to include ${PROJECT_BINARY_DIR}
# target_include_directories(Tutorial PUBLIC
#                            "${PROJECT_BINARY_DIR}"
#                            )
