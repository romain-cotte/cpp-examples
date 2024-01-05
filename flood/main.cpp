#include <sstream>


#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "gdal_priv.h"
#include "cpl_conv.h" // for CPLMalloc()


#include "./opentopography.h"

using namespace std;
using namespace rapidjson;


int main(int argc, char **argv) {
  GDALAllRegister();


  // Point point(-119, 37.0);
  // float distance = 1.0;
  // int r = OpenTopography::get("ex1.tif", point, distance);
  // if (!r) return 1;



  return 0;
}
