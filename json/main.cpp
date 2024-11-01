#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>
#include <set>

using namespace std;

struct T {
  double latency;
  int cnt;
  set<string> operations;
};


map<string, T> mp_by_service;
map<string, T> mp_by_operation;


void parse_line(const string& line) {
  size_t json_start = line.find('{');
  if (json_start == string::npos) {
    // cerr << "Aucun JSON trouvé dans la ligne." << endl;
    return;
  }

  string json_text = line.substr(json_start);

  Json::CharReaderBuilder readerBuilder;
  Json::Value jsonData;
  string errs;

  istringstream jsonStream(json_text);
  if (!Json::parseFromStream(readerBuilder, jsonStream, &jsonData, &errs)) {
    cerr << "Error on json parse: " << errs << endl;
    return;
  }

  string log_level = jsonData["_logLevel"].asString();
  string msg = jsonData["_msg"].asString();
  string queryHash = jsonData["queryHash"].asString();
  string operation_name = jsonData["operationName"].asString();
  string clientName = jsonData["clientName"].asString();
  double latency = jsonData["latency"].asDouble();

  mp_by_service[clientName].latency += latency;
  mp_by_service[clientName].cnt ++;
  mp_by_service[clientName].operations.insert(operation_name);

  mp_by_operation[operation_name].latency += latency;
  mp_by_operation[operation_name].cnt ++;


  // cout << "log_level: " << log_level << endl;
  // cout << "Message: " << msg << endl;
  // cout << "QueryHash: " << queryHash << endl;
  // cout << "operation_name: " << operation_name << endl;
  // cout << "ClientName: " << clientName << endl;
  // cout << "Latency: " << latency << " ms" << endl;
  // cout << "-------------------------" << endl;
}


int main() {
  ifstream file("logs.txt");
  string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      parse_line(line);
    }
  }

  cout << "======== SERVICES ========" << endl;

  for (auto [service, t]: mp_by_service) {
    cout << "--- " << service << " ---" << endl;
    cout << "cnt: " << t.cnt << endl;
    cout << "latency: " << t.latency << endl;
    cout << "operations: ";
    for (string operation_name: t.operations) {
      cout << operation_name << " ";
    }
    cout << endl;
  }

  cout << endl;
  cout << "======== OPERATIONS ========" << endl;


  for (auto [operation, t]: mp_by_operation) {
    cout << "--- " << operation << " ---" << endl;
    cout << "cnt: " << t.cnt << endl;
    cout << "latency: " << t.latency << endl;
    cout << "average: " << t.latency / t.cnt << endl;
    cout << endl;
  }

  return 0;
}


