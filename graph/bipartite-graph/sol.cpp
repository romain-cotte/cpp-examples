#ifndef SOL_CPP
#define SOL_CPP

#include <vector>

using namespace std;


bool sol_matching(const vector<vector<int>> &G, vector<int> &parent, int u, vector<int> &vis, int cookie) {
  assert(u < (int)vis.size());
  if (vis[u] == cookie) return false;
  vis[u] = cookie;
  for (auto v: G[u]) {
    if (parent[v] == -1) {
      parent[v] = u;
      return true;
    }
    if (sol_matching(G, parent, parent[v], vis, cookie)) {
      parent[v] = u;
      return true;
    }
  }
  return false;
}

int sol_matches(const vector<vector<int>> &G) {
  int n = G.size();
  int ans = 0;
  vector<int> vis(n, false);
  vector<int> parent(n, -1);
  int cookie = 0;
  for (int u = 0; u < n; ++u) {
    ++cookie;
    ans += sol_matching(G, parent, u, vis, cookie);
  }
  return ans;
}

#endif /* SOL_CPP */
