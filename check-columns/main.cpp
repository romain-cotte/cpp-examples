/**
 * Fenwick tree
 */
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <time.h>
#include <vector>

using namespace std;

int main(int argc, const char **argv) {
  clock_t time = clock();
  if (argc != 3) {
    cout << "Usage:" << endl;
    cout << "./check-columns <file> <column_nb>" << endl;
    return 1;
  }
  cout << "Checking file:" << argv[1] << endl;

  string line;
  int count, lineNumber = 1;
  int refCount = atoi(argv[2].c_str());
  std::ifstream infile(argv[1]);

  while (std::getline(infile, line)) {
    count = 0;
    for (int i = 0, l = line.size(); i < l; i++) {
      if (line[i] == '|') {
        count++;
      }
      if (count != refCount) {
        cout << "Error on line " << lineNumber << endl;
        cout << line << endl;
      }
    }
    lineNumber++;
  }

  printf("Time %d clocks, %.3f milliseconds.\n",
         (int)time,
         ((float)time)/CLOCKS_PER_SEC * 1000);
  return 0;
}
