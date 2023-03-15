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
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>
#include <netcdf>

using namespace std;

using namespace netCDF;
using namespace netCDF::exceptions;

void display_header_group(NcGroup nc_group) {
cout << "dimensions:" << endl;
  for (auto [name, nc_dim]: nc_group.getDims()) {
    cout << "   " << name << " = " << nc_dim.getSize() << " ;" << endl;
  }

  cout << "variables:" << endl;
  for (auto [name, nc_var]: nc_group.getVars()) {
    NcType nc_type = nc_var.getType();
    cout << "  " << nc_type.getName() << " " << nc_var.getName() << "(";
    for (int i = 0; i < nc_var.getDimCount(); ++i) {
      if (i != 0) {
        cout << ", ";
      }
      NcDim nc_dim = nc_var.getDim(i);
      cout << nc_dim.getName();
    }
    cout << ");" << endl;

    for (auto [s, nc_var_att]: nc_var.getAtts()) {
      NcType nc_type = nc_var_att.getType();
      cout << "    " << name << ":" << s << "(" << nc_type.getName() << ")";

      NcVarAtt att = nc_var.getAtt(s);

      if (nc_type.getName() == "char") {
        string units;
        att.getValues(units);
        cout << " = \"" << units << "\"";
      }
      if (nc_type.getName() == "double") {
        double *d = new double;
        att.getValues(d);
        cout << " = " << *d;
      }
      if (nc_type.getName() == "float") {
        float *f = new float;
        att.getValues(f);
        cout << " = " << *f;
      }
      cout << endl;
    }
  }
}



int main(int argc, const char **argv) {
  NcFile nc_file("./data/era5_Tmax_40.0_0.0_projection_2030.nc", NcFile::read);
  // NcFile nc_file("./data/regions.nc", NcFile::read);

  string data_name = nc_file.getName(false);
  cout << data_name << endl;


  cout << nc_file.getName(true) << endl;
  cout << nc_file.getId() << endl;
  cout << nc_file.isRootGroup() << endl;
  cout << nc_file.getVarCount() << endl;

  for (auto [name, nc_group]: nc_file.getGroups()) {
    cout << "::" << name << endl;
  }

  display_header_group(nc_file);

  return 0;
}

// netcdf era5_Tmax_40.0_0.0_projection_2030 {
// dimensions:
//   date = 10950 ;
//   latitude = 40 ;
//   longitude = 40 ;
// variables:
//   float tasmax(date, latitude, longitude) ;
//     tasmax:_FillValue = NaNf ;
//   int date(date) ;
//     date:units = "days since 2015-01-01" ;
//     date:calendar = "proleptic_gregorian" ;
//   double latitude(latitude) ;
//     latitude:_FillValue = NaN ;
//     latitude:units = "degrees_north" ;
//   double longitude(longitude) ;
//     longitude:_FillValue = NaN ;
//     longitude:units = "degrees_east" ;
// }

// variables:
//   int date(date);
//     date:calendar
//     date:units
//   double latitude(latitude);
//     latitude:_FillValue
//     latitude:units
//   double longitude(longitude);
//     longitude:_FillValue
//     longitude:units
//   float tasmax(date, latitude, longitude);
//     tasmax:_FillValue
