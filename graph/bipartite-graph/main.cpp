#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>

#define SZ(x) (int)(x.size())
#define F0(i,n) for(int i=0;i<n;i++)
#define F1(i,n) for(int i=1;i<=n;i++)
#define FI(i,n) for(int i=0;i<=n;i++)
#define TR(x) cout << #x << " = " << x << endl
#define FE(k) get<0>(k)
#define SE(k) get<1>(k)
#define TH(k) get<2>(k)
#define _ << " " <<
#define INF 1E9

using namespace std;
typedef vector<int> vi;

template<typename T> void remin(T& a, const T& b) { if (b < a) a = b; }
template<typename T> void remax(T& a, const T& b) { if (b > a) a = b; }

int M, NA, NB, cookie;
int parent[105], visited[105];
vi G[105];


bool matching(int u) {
  if (visited[u] == cookie) return false;
  visited[u] = cookie;
  for (auto v: G[u]) {
    if (!parent[v]) {
      parent[v] = u;
      return true;
    }
    // if (parent[v] == u) continue;
    if (matching(parent[v])) {
      parent[v] = u;
      return true;
    }
  }
  return false;
}

int main(int argc, const char **argv) {
  int u, v;
  while (1) {
    scanf("%d", &M);
    if (!M) break;
    for (int i = 0; i < M; ++i) {
      scanf("%d%d", &u, &v);
      remax(NA, u);
      remax(NB, v);
      G[u].push_back(v);
    }
    int matches = 0;
    for (int i = 1; i <= NA; ++i) {
      cookie++;
      if (matching(i)) matches++;
    }
    printf("%d\n", matches);
  }
  return 0;
}
