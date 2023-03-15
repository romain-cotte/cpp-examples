# Generate netcdf for regions.cdl

```sh
ncgen -k 3 -l C data/regions.cdl > data/regions.c
ncgen -k 3 data/regions.cdl
```

# Installation

```sh
make build
cd build
cmake ..
make
```
