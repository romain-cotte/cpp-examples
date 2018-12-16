/**
 * Problem: 610
 */
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <typeinfo>
#include <vector>

#define SZ(x) (int)(x.size())
#define F0(i,n) for(int i=0;i<n;++i)
#define F1(i,n) for(int i=1;i<=n;++i)
#define TR(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

using namespace std;

typedef long long ll;
typedef vector<vector<int> > vvi;
typedef vector<int> vi;
typedef vector<string> vs;

map<int, vector<int>> Q;
int N, M;

int dfs_num[1005], dfs_low[1005], on_stack[1005];
int connected_component[1005];

int curr, root, children_root;
deque<int> dfs_queue;

void print_queue(deque<int> q) {
  cout << "queue: ";
  for (auto el: q) {
    cout << el << " ";
  }
  cout << endl;
}

void tarjan(int u) {
  dfs_num[u] = dfs_low[u] = curr++;
  on_stack[u] = 1;
  dfs_queue.push_back(u);

  for (auto v: Q[u]) {
    if (!dfs_num[v]) {
      tarjan(v);
    }
    if (on_stack[v]) {
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
  }
  if (dfs_num[u] == dfs_low[u]) {
    cout << "SCC: ";
    while (!dfs_queue.empty() && dfs_queue.back() != u) {
      int v = dfs_queue.back();
      std::cout << v << " ";
      dfs_queue.pop_back();
      on_stack[v] = 0;
    }
    int v = dfs_queue.back();
    std::cout << v << " ";
    dfs_queue.pop_back();
    on_stack[v] = 0;
    cout << endl;
  }
}


int main(int argc, const char **argv) {
  int u, v, k = 1;

  while (1) {
    cin >> N >> M;
    if (!N && !M) break;
    cout << k++ << endl << endl;
    curr = 1;
    Q.clear();
    memset(dfs_num, 0, sizeof(dfs_num));
    memset(dfs_low, 0, sizeof(dfs_low));
    memset(connected_component, 0, sizeof(connected_component));
    F0(i, M) {
      cin >> u >> v;
      if (Q.count(u)) {
        Q[u].push_back(v);
      } else {
        Q[u] = { v };
      }
    }

    int total = 0;
    F1(i, N) {
      if (!dfs_num[i]) {
        tarjan(i);
      }
      dfs_queue.clear();
    }

  }
  return 0;
}
