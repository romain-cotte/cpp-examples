# Install curlpp

https://github.com/jpbarrette/curlpp.git

Get include library:

```sh
pkg-config --libs --cflags curlpp
curlpp-config --cflags
curlpp-config --libs
```

```sh
pkg-config --libs --cflags gdal
```

```sh
gdalsrsinfo --single-line ex1.tf
gdalsrsinfo -e ex1.tf
```


Open topography
api key: aeccb70d03e3cc52600a0c331f88e06c


```sh
url=
curl -X GET "https://portal.opentopography.org/API/globaldem?demtype=SRTMGL3&south=36.738884&north=38.091337&west=-120.168457&east=-118.465576&outputFormat=GTiff&API_Key=aeccb70d03e3cc52600a0c331f88e06c" -H "accept: */*"
```
