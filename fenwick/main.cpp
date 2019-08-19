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
typedef vector<int> vi;
#define SIZE 100


/**
 * Give the prefix sum, be very careful when inserting, it starts from 1
 * In addition, it should be globally instantiated for initialization of array
 * bit
 */
struct Fenwick_Tree {
  int bit[SIZE];
  inline int low_bit(int idx) { return idx&(-idx); }
  int sum(int idx) {
    int total = 0;
    while (idx > 0) {
      total += bit[idx];
      idx -= low_bit(idx);
    }
    return total;
  }
  void insert(int idx, int v) {
    while (idx < SIZE) {
      bit[idx] += v;
      idx += low_bit(idx);
    }
  }
  int query(int l, int r) {
    return sum(r) - sum(l-1);
  }
} ft;


int main(int argc, const char **argv) {
  clock_t time = clock();
  vi v = { 1, 3, 4, 5, 10, 2 };
  for (int i = 1, l = v.size(); i <= l; ++i) {
    ft.insert(i, v[i-1]);
  }
  // ft.insert(1, 10);
  printf("%d\n", ft.query(3, 6));

  time = clock() - time;
  printf("Time %d clocks, %.3f milliseconds.\n",
         (int)time,
         ((float)time)/CLOCKS_PER_SEC * 1000);
  return 0;
}
