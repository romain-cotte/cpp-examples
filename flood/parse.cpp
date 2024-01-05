#include <sstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

// using namespace rapidjson;
using namespace std;
// using namespace curlpp::options;


int main(int argc, char **argv) {

  rapidjson::Document document;
  document.Parse("{\"hello\":  \"world \"}");

  cout << document["hello"].GetString() << endl;


  return 0;
}
