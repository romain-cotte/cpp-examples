#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
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

vector<size_t> get_dimensions(const NcGroup &nc_group) {
  vector<size_t> dim;
  for (auto [name, nc_dim]: nc_group.getDims()) {
    dim.push_back(nc_dim.getSize());
  }
  return dim;
}

void display_dimensions(const NcGroup &nc_group, int depth = 0) {
  string prefix(2*depth, ' ');
  cout << prefix << "  dimensions:" << endl;
  for (auto [name, nc_dim]: nc_group.getDims()) {
    cout << prefix  << "   " << name << " = " << nc_dim.getSize() << " ;" << endl;
  }
  // return dim;
}

void display_variables(const NcGroup &nc_group, int depth = 0) {
  string prefix(2*depth, ' ');

  cout << prefix << "  variables:" << endl;
  for (auto [name, nc_var]: nc_group.getVars()) {
    NcType nc_type = nc_var.getType();
    cout << prefix << "   " << nc_type.getName() << " " << nc_var.getName() << "(";
    for (int i = 0; i < nc_var.getDimCount(); ++i) {
      if (i != 0) {
        cout << ", ";
      }
      NcDim nc_dim = nc_var.getDim(i);
      cout << nc_dim.getName();
    }
    cout << ");" << endl;

    // if (nc_type.getName() == "float") {
    //   float arr[];
    //   nc_var.getVar(arr);
    //   for (int i = 0; i < 10; ++i) {
    //     printf("%f\n", arr[i]);
    //   }
    // }

    for (auto [s, nc_var_att]: nc_var.getAtts()) {
      NcType nc_type = nc_var_att.getType();
      cout << prefix << "    " << name << ":" << s << "(" << nc_type.getName() << ")";

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

void display_header_group(NcGroup nc_group, int depth = 0) {
  // cout << "name       : " << nc_group.getName(true) << endl;
  // cout << "is null    : " << nc_group.isNull() << endl;
  // cout << "id         : " << nc_group.getId() << endl;
  // cout << "group count: " << nc_group.getGroupCount() << endl;
  // cout << "getVarCount: " << nc_group.getVarCount() << endl;
  string prefix(2*depth, ' ');

  cout << prefix << "group: " << nc_group.getName(false) << " {" << endl;
  if (nc_group.getVarCount()) {
    display_dimensions(nc_group, depth);
    display_variables(nc_group, depth);
  }
  if (nc_group.getGroupCount()) {
    cout << endl;
  }
  for (auto [name, subgroup]: nc_group.getGroups()) {
    display_header_group(subgroup, depth+1);
  }
  cout << prefix << "}" << endl;
}


int main(int argc, const char **argv) {

  // string data_name = nc_file.getName(false);
  // display_header_group(nc_file);


  clock_t t_clock = clock();

  NcFile nc_file("./data/era5_Tmax_40.0_0.0_projection_2030.nc", NcFile::read);
  // NcFile nc_file("./data/regions.nc", NcFile::read);

  float *data_in = new float[10950*40*40];

  // Retrieve the variable named "data"
  auto data = nc_file.getVar("tasmax");
  if (data.isNull()) {
    printf("Error");
    return 1;
    // return nc_err;
  }
  data.getVar(data_in);

  fprintf(
    stderr,
    "Time %.3f milliseconds.\n",
    ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000
  );

  float mx = data_in[0];
  float mn = data_in[0];
  for (int i = 0; i < 10950*40*40; ++i) {
    if (mx < data_in[i]) {
      mx = data_in[i];
    }
    if (data_in[i] < mn) {
      mn = data_in[i];
    }
    // printf("%f\n", data_in[i]);
  }
  printf("%f\n", mx);
  printf("%f\n", mn);

  fprintf(
    stderr,
    "Time %.3f milliseconds.\n",
    ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000
  );
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
