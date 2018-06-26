#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <limits>
#include <sstream>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <map>
#include <assert.h>

using namespace std;


struct MyStruct {
  int id;
  MyStruct() : id(42) {
  }
  void print() {
    cout << "id: " << id << endl;
  }
};

int main(int argc, const char **argv) {
  clock_t time = clock();

  map<int, int> m;

  m.insert(pair<int, int>(5, 6));
  assert(m[5] == 6);
  m.insert(pair<int, int>(5, 8)); // Not working !
  assert(m[5] == 6);
  m[5] = 8;
  assert(m[5] == 8);

  for (map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
    assert(it->first == 5);
    assert(it->second == 8);
  }

  map<int, int>::iterator el = m.find(5);
  if (el != m.end()) {
    assert(el->second == 8);
  }

  el = m.find(0);
  assert(el == m.end());

  assert(m.size() == 1);

  /**
   * map with a struct
   */
  map<int, MyStruct> structMap;
  // Impossible :
  // map<MyStruct, int> structMap2;

  MyStruct *a = new MyStruct();
  MyStruct b = MyStruct();

  structMap.insert(pair<int, MyStruct>(5, *a));
  structMap.insert(pair<int, MyStruct>(4, b));
  assert(structMap.size() == 2);

  time = clock() - time;
  printf("Time %d clocks, %.3f milliseconds.\n",
         (int)time,
         ((float)time)/CLOCKS_PER_SEC * 1000);
  return 0;
}
