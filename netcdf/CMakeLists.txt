cmake_minimum_required(VERSION 3.16)

project(NetcdfReader VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENV{CPATH} /usr/include/hdf5/serial/)


set(DEP_ROOT_DIR ${CMAKE_SOURCE_DIR}/external-${CMAKE_SYSTEM_NAME})

if(NOT EXISTS ${DEP_ROOT_DIR})
  file(MAKE_DIRECTORY ${DEP_ROOT_DIR})
endif()

include(cmake/netcdf.cmake)
find_package(CURL REQUIRED)


# list(APPEND CMAKE_PREFIX_PATH ${DEP_ROOT_DIR}/${NETCDF_NAME})
# list(APPEND CMAKE_PREFIX_PATH cmake)
# message("CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}")
# message("find_package netCDFCxx")
# find_package(netCDFCxx REQUIRED)


include_directories(${DEP_ROOT_DIR}/${NETCDF_NAME}/cxx4)
link_directories(${DEP_ROOT_DIR}/${NETCDF_NAME}/build)

add_executable(netcdf_reader main.cpp)

target_link_libraries(netcdf_reader netcdf-cxx4)
# target_link_libraries(netcdf_reader netCDF)

# target_link_libraries(netcdf_reader netCDF::netcdf)
