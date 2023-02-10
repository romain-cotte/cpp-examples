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

message("Configuring ${NETCDF_NAME}...")

# file(REMOVE_RECURSE ${DEP_ROOT_DIR}/${NETCDF_NAME}/build)
file(MAKE_DIRECTORY ${DEP_ROOT_DIR}/${NETCDF_NAME}/build)


if(NOT EXISTS ${DEP_ROOT_DIR}/${NETCDF_NAME}/build/plugins/libmisc.so)
    message("Configuring ${NETCDF_NAME} locally...")
    execute_process(COMMAND ${CMAKE_COMMAND}
                    "-DCMAKE_FIND_LIBRARY_SUFFIXES=.a"
                    # "-DBUILD_SHARED_LIBS=OFF"
                    "-H${DEP_ROOT_DIR}/${NETCDF_NAME}"
                    "-B${DEP_ROOT_DIR}/${NETCDF_NAME}/build"
                    RESULT_VARIABLE
                    NETCDF_CONFIGURE)
    if(NOT NETCDF_CONFIGURE EQUAL 0)
        message(FATAL_ERROR "${NETCDF_NAME} configure failed!")
    endif()

    message("Building ${NETCDF_NAME} locally...")
    message(${DEP_ROOT_DIR}/${NETCDF_NAME}/build/plugins/libmisc.so)
    execute_process(COMMAND ${CMAKE_COMMAND} --build
                    "${DEP_ROOT_DIR}/${NETCDF_NAME}/build"
                    RESULT_VARIABLE
                    NETCDF_BUILD)
endif()


if(NOT EXISTS ${DEP_ROOT_DIR}/install/bin/ncxx4-config)
    message(${DEP_ROOT_DIR}/install/bin/ncxx4-config)
    message("Installing ${NETCDF_NAME} locally...")
    execute_process(COMMAND ${CMAKE_COMMAND} --install
                    "${DEP_ROOT_DIR}/${NETCDF_NAME}/build"
                    --prefix "${DEP_ROOT_DIR}/install"
                    RESULT_VARIABLE
                    NETCDF_BUILD)
endif()

message("NCXX_LIB_VERSION ${NCXX_LIB_VERSION}")
