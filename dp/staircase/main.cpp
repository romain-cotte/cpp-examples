/**
 *
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
#define N 100

int waysMem[200];

int countWays(int n) {
  if (waysMem[n]) return waysMem[n];
  if (n < 0) return 0;
  if (n == 0) return 1;
  return waysMem[n] = countWays(n - 3) + countWays(n - 2) + countWays(n - 1);
}

int main(int argc, const char **argv) {
  memset(waysMem, 0, sizeof(waysMem));
  std::cout << "countWays(1):" << countWays(1) << std::endl;
  std::cout << "countWays(2):" << countWays(2) << std::endl;
  std::cout << "countWays(3):" << countWays(3) << std::endl;
  std::cout << "countWays(4):" << countWays(4) << std::endl;
  std::cout << "countWays(5):" << countWays(5) << std::endl;
  std::cout << "countWays(6):" << countWays(6) << std::endl;
  return 0;
}
