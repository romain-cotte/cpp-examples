#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <iterator>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>

#include "ogrsf_frmts.h"

#define INF 1E9
#define INF64 2E18

using namespace std;

template<class T1, class T2> void pr(const pair<T1,T2>& x);
template<class T, size_t SZ> void pr(const array<T,SZ>& x);
template<class T> void pr(const vector<T>& x);
template<class T, class C> void pr(const set<T,C>& x);
template<class T, class C> void pr(const multiset<T,C>& x);
template<class T1, class T2> void pr(const map<T1,T2>& x);
template<class... T> void pr(const tuple<T...>& tup);

template<class T> void pr(const T& x) { cout << x; }
template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
  pr(first); pr(rest...);
}
template<class T1, class T2> void pr(const pair<T1,T2>& x) {
  pr("{",x.first,", ",x.second,"}");
}
template<class T> void prContain(const T& x) {
  pr("{");bool fst = 1; for(auto &a: x) pr(!fst?", ":"",a), fst = 0;pr("}");
}
template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
template<class T> void pr(const vector<T>& x) { prContain(x); }
template<class T, class C> void pr(const set<T,C>& x) { prContain(x); }
template<class T, class C> void pr(const multiset<T,C>& x) { prContain(x); }
template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }

template<class T, size_t... I>
void pr(const T& tup, index_sequence<I...>) {
  pr("("); (..., (cout << (I == 0? "" : ", ") << get<I>(tup))); pr(")");
}
template<class... T>
void pr (const tuple<T...>& tup) {
  pr(tup, make_index_sequence<sizeof...(T)>());
}
void ps() { pr("\n"); }
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
  pr(first," "); ps(rest...);
}

template<typename T> int remin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<typename T> int remax(T& a,const T& b){if(b>a){a=b;return true;}return false;}

typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int main(int argc, const char **argv) {
  GDALAllRegister();

  GDALDataset *poDS;

  poDS = (GDALDataset*) GDALOpenEx("./map/map.shp", GDAL_OF_VECTOR, NULL, NULL, NULL);
  if (poDS == NULL) {
      printf("Open failed.\n");
      exit(1);
  }
  printf("%d\n", poDS->GetLayerCount());

  OGRLayer  *poLayer;
  poLayer = poDS->GetLayer(0);
  if (poLayer == NULL) {
    printf("Layer is null\n");
    exit(1);
  }

  for (const auto& poFeature: *poLayer) {
    for (const auto& oField: *poFeature) {
      switch (oField.GetType()) {
        case OFTInteger:
          printf("%d,", oField.GetInteger());
          break;
        case OFTInteger64:
          printf(CPL_FRMT_GIB ",", oField.GetInteger64());
          break;
        case OFTReal:
          printf("%.3f,", oField.GetDouble());
          break;
        case OFTString:
          printf("%s,", oField.GetString());
          break;
        default:
          printf("%s,", oField.GetAsString());
          break;
      }
    }
    const OGRGeometry *poGeometry = poFeature->GetGeometryRef();

    if (poGeometry != nullptr
            && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint) {
      const OGRPoint *poPoint = poGeometry->toPoint();
      printf("%.3f,%3.f\n", poPoint->getX(), poPoint->getY());
    } else {
      printf("no point geometry\n");
    }

    // OGRwkbGeometryType type = wkbFlatten(poGeometry->getGeometryType());
    // printf("type: %d\n", type);
    // const OGRPolygon *poPolygon = poGeometry->toPolygon();
    // if (poPolygon == NULL) {
    //   printf("error\n");
    // }

    printf("%s\n", poGeometry->exportToJson());
  }
  return 0;
}
