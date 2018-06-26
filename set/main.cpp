/**
 * Set
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <sstream>
#include <ctime>
#include <time.h>
#include <assert.h>

using namespace std;

int main(int argc, const char **argv) {
  clock_t time = clock();

  set<int> s;
  s.insert(10);
  s.insert(16);
  s.insert(35);
  assert(s.find(35) != s.end());
  assert(s.size() == 3);
  s.erase(35);
  assert(s.size() == 2);
  s.erase(45);
  assert(s.size() == 2);
  s.clear();
  assert(s.size() == 0);



  time = clock() - time;
  printf("Time %d clocks, %.3f milliseconds.\n",
         (int)time,
         ((float)time)/CLOCKS_PER_SEC * 1000);
  return 0;
}
