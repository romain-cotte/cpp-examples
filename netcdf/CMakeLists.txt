cmake_minimum_required(VERSION 3.16)

project(NetcdfReader VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

message("Build type ${CMAKE_BUILD_TYPE}")


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

set(ENV{CPATH} /usr/include/hdf5/serial/)


set(DEP_ROOT_DIR ${CMAKE_SOURCE_DIR}/external-${CMAKE_SYSTEM_NAME})

if(NOT EXISTS ${DEP_ROOT_DIR})
  file(MAKE_DIRECTORY ${DEP_ROOT_DIR})
endif()

include(cmake/netcdf.cmake)
find_package(CURL REQUIRED)

if (MACOSX)
  execute_process(COMMAND nc-config --includedir OUTPUT_VARIABLE NETCDF_C_INCLUDE)
  include_directories(${NETCDF_C_INCLUDE})
endif()

if (MACOSX)
  link_directories(${DEP_ROOT_DIR}/install/lib/libnetcdf-cxx4.dylib)
else()
  link_directories(${DEP_ROOT_DIR}/install/lib/libnetcdf-cxx4.so)
endif()

include_directories(${DEP_ROOT_DIR}/${NETCDF_NAME}/cxx4)


link_directories(${DEP_ROOT_DIR}/install/lib)

add_executable(netcdf_reader src/main.cpp)

target_link_libraries(netcdf_reader netcdf-cxx4)
