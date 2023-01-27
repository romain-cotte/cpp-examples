# Download and build NETCDF

set(NETCDF_VERSION 4.3.1)
set(NETCDF_NAME netcdf-cxx4-${NETCDF_VERSION})
set(NETCDF_TAR_PATH ${DEP_ROOT_DIR}/${NETCDF_NAME}.tar.gz)

if(NOT EXISTS ${NETCDF_TAR_PATH})
    message(STATUS "Downloading https://downloads.unidata.ucar.edu/netcdf-cxx/${NETCDF_VERSION}/netcdf-cxx4-${NETCDF_VERSION}.tar.gz")
    file(DOWNLOAD https://downloads.unidata.ucar.edu/netcdf-cxx/${NETCDF_VERSION}/netcdf-cxx4-${NETCDF_VERSION}.tar.gz ${NETCDF_TAR_PATH})
endif()

if(NOT EXISTS ${DEP_ROOT_DIR}/${NETCDF_NAME})
    message(STATUS "Extracting ${NETCDF_NAME}...")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${NETCDF_TAR_PATH} WORKING_DIRECTORY ${DEP_ROOT_DIR}/)
endif()


# if(NOT EXISTS ${DEP_ROOT_DIR}/${NETCDF_NAME}/build/libs2.a)

message("Configuring ${NETCDF_NAME}...")

file(REMOVE_RECURSE ${DEP_ROOT_DIR}/${NETCDF_NAME}/build)
file(MAKE_DIRECTORY ${DEP_ROOT_DIR}/${NETCDF_NAME}/build)


message("Configuring ${NETCDF_NAME} locally...")
execute_process(COMMAND ${CMAKE_COMMAND}
                "-DCMAKE_FIND_LIBRARY_SUFFIXES=.a"
                "-DBUILD_SHARED_LIBS=OFF"
                "-H${DEP_ROOT_DIR}/${NETCDF_NAME}"
                "-B${DEP_ROOT_DIR}/${NETCDF_NAME}/build"
                RESULT_VARIABLE
                NETCDF_CONFIGURE)
if(NOT NETCDF_CONFIGURE EQUAL 0)
    message(FATAL_ERROR "${NETCDF_NAME} configure failed!")
endif()

message("Building ${NETCDF_NAME} locally...")
execute_process(COMMAND ${CMAKE_COMMAND} --install
                "${DEP_ROOT_DIR}/${NETCDF_NAME}/build"
                RESULT_VARIABLE
                NETCDF_BUILD)


message("NCXX_LIB_VERSION ${NCXX_LIB_VERSION}")

# if(NOT NETCDF_BUILD EQUAL 0)
#     message(FATAL_ERROR "${NETCDF_NAME} build failed!")
# endif()

# endif()
