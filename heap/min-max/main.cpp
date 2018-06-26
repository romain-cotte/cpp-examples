/**
 * Min-max heap
 * See https://en.wikipedia.org/wiki/Min-max_heap
 */
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <time.h>
#include <vector>

using namespace std;
typedef vector<string> vs;
typedef long long ll;
typedef long long int lli;
typedef pair<int, int> pii;

vector<int> heap;


int main(int argc, const char **argv) {
  clock_t time = clock();
  int arr[] = {15, 5, 6, 20, 15, 25, 19, 463, 74, 0};

  for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {

  }

  time = clock() - time;
  printf("Time %d clocks, %.3f milliseconds.\n",
         (int)time,
         ((float)time)/CLOCKS_PER_SEC * 1000);
  return 0;
}
