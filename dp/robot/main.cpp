/**

Imagine a robot sitting on the upper left comer of an X by Ygrid. The robot can
only move in two directions: right and down. How many possible paths are there
for the robot to go from (0, 0) to (X, Y) ?

FOLLOW UP Imagine certain spots are "off limits," such that the robot cannot
step on them. Design an algorithm to find a path for the robot from the top left
to the bottom right.

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
#define SIZE 200

int waysMem[SIZE][SIZE];
int forbidden[SIZE][SIZE];

int countWays(int x, int y) {
  if (waysMem[x][y]) return waysMem[x][y];
  if (forbidden[x][y]) return 0;
  if (x == 0 && y == 0) return 1;
  if (x == 0) return countWays(0, y-1);
  if (y == 0) return countWays(x-1, 0);
  return waysMem[x][y] = countWays(x - 1, y) + countWays(x, y - 1);
}

int main(int argc, const char **argv) {
  memset(waysMem, 0, sizeof(waysMem));
  memset(forbidden, 0, sizeof(forbidden));
  forbidden[1][1] = 1;
  std::cout << "countWays(2, 1):" << countWays(2, 1) << std::endl;
  std::cout << "countWays(2, 2):" << countWays(2, 2) << std::endl;
  return 0;
}
