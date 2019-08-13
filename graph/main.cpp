/**
 * Given a directed graph, design an algorithm to find out whether there is a
 * route between two nodes.
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
#include <unordered_set>
#include <map>
#include <set>
#include <sstream>
#include <time.h>
#include <vector>

using namespace std;

struct Graph {
  int value;
  Graph *left;
  Graph *right;
};

class Graph {
private:
  Graph *left;
  Graph *right;
  int value;
public:
  Graph(){}

};

int bfs(int source, int sink) {
  queue<ii> q;
  memset(visited, 0, sizeof(visited));
  q.push(make_pair(source, INT_MAX));
  int u, cap;
  while (!q.empty()) {
    tie(u, cap) = q.front();
    if (u == sink) {
      while (u != source) {
        res[parent[u]][u] -= cap;
        res[u][parent[u]] += cap;
        u = parent[u];
      }
      return cap;
    }
    q.pop();
    for (int i = 0; i < N; ++i) {
      if (visited[v]) continue;
      if (res[u][v] > 0) {
        visited[v] = true;
        parent[v] = u;
        q.push(make_pair(v, min(cap, res[u][v])));
      }
    }
  }
  return 0;
}

int edmonds_karp(int source, int sink) {
  int total = 0, increase;
  while (increase = bfs(source, sink)) {
    total += increase;
  }
  return total;
}

int main(int argc, const char **argv) {
  return 0;
}
