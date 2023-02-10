# Installation

 * try to install from cmake instead of using Makefile


# Compile netcdf with cmake

```sh
# cmake \
# -DCMAKE_FIND_LIBRARY_SUFFIXES=.a \
# -DBUILD_SHARED_LIBS=OFF \
# "-Hexternal-Linux/netcdf-cxx4-4.3.1" \
# "-Bexternal-Linux/netcdf-cxx4-4.3.1/build"

export CPATH="/usr/include/hdf5/serial/"

cmake --build \
"external-Linux/netcdf-cxx4-4.3.1/build"


cmake \
"-Hexternal-Linux/netcdf-cxx4-4.3.1" \
"-Bexternal-Linux/netcdf-cxx4-4.3.1/build"

cmake --install "external-Darwin/netcdf-cxx4-4.3.1/build" \
--prefix "/home/romain/perso/cpp/cpp-examples/netcdf/installation"
```


# Darwin

```sh
cmake \
"-Hexternal-Darwin/netcdf-cxx4-4.3.1" \
"-Bexternal-Darwin/netcdf-cxx4-4.3.1/build"

# Missing make step
cmake "-Bexternal-Darwin/netcdf-cxx4-4.3.1/build"

cmake --install "external-Darwin/netcdf-cxx4-4.3.1/build" \
--prefix "/Users/romaincotte/perso/cpp/cpp-examples/netcdf/installation"
```
