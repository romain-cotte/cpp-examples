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
#define SIZE 100

int tab[SIZE];

int sum(int i) {
  int total = 0;
  while (i > 0) {
    total += tab[i];
    i -= i & -i;
  }
  return total;
}
void add(int i, int k) {
  while (i < SIZE) {
    tab[i] += k;
    i += i & -i;
  }
}

int sumFromTo(int f, int t) {
  return sum(t) - sum(f);
}

int main(int argc, const char **argv) {
  clock_t time = clock();
  memset(tab, 0, sizeof(tab));
  cout << "Hello" << endl;
  add(3, 10);
  add(2, 100);
  cout << "1 " << sum(1) << endl;
  add(5, 13);
  cout << "2 " << sum(2) << endl;
  cout << "2 " << sum(2) << endl;
  cout << "3 " << sum(3) << endl;
  cout << "4 " << sum(4) << endl;
  cout << "7 " << sum(7) << endl;
  cout << "sumFromTo 4 7 " << sumFromTo(4, 7) << endl;

  time = clock() - time;
  printf("Time %d clocks, %.3f milliseconds.\n",
         (int)time,
         ((float)time)/CLOCKS_PER_SEC * 1000);
  return 0;
}
