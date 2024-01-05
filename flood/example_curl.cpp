#include <sstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include "./opentopography.h"


using namespace std;
using namespace rapidjson;

int main(int argc, char **argv) {
  try {
    // That's all that is needed to do cleanup of used resources (RAII style).
    curlpp::Cleanup myCleanup;

    // Our request to be sent.
    curlpp::Easy myRequest;

    // Set the URL.
    myRequest.setOpt<curlpp::options::Url>("https://jsonplaceholder.typicode.com/todos/1");

    // rapidjson::Reader reader;
    // char readBuffer[65536];
    // rapidjson::FileReadStream is(stdin, readBuffer, sizeof(readBuffer));

    std::ostringstream os;
    curlpp::options::WriteStream ws(&os);
    myRequest.setOpt(ws);

    // Send request and get a result.
    // By default the result goes to standard output.
    myRequest.perform();
    rapidjson::Document document;
    string s = os.str();

    document.Parse<0>(s.c_str());
    cout << document["userId"].GetInt() << endl;
    cout << document["id"].GetInt() << endl;
    cout << document["title"].GetString() << endl;
    cout << document["completed"].GetBool() << endl;

    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    // Accept() traverses the DOM and generates Handler events.
    document.Accept(writer);
    printf("%s\n", sb.GetString());
  }

  catch (curlpp::RuntimeError & e) {
    std::cout << e.what() << std::endl;
  }

  catch (curlpp::LogicError & e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
