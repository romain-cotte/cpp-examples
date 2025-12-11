Contains a cycle
10 5
1 2
1 6
1 8
2 3
2 6

Does not contain a cycle
10 4
1 2
1 6
1 8
2 3




```cpp
/**
 * DOES NOT WORK!!!
 *
 * Counter example
 * 1 2
 * 2 5
 * 1 3
 * 3 5
 *
 */

function<bool(int)> dfs_is_cyclic_wrong;
dfs_is_cyclic_wrong = [&](int u) {
  vis[u] = cookie;
  for (int v: G[u]) {
    if (vis[v] == cookie) return true;
    if (!vis[v]) {
      if (dfs_wrong(v)) return true;
    }
  }
  return false;
};


auto is_cyclic_wrong = [&]() {
  for (int u = 1; u <= n; ++u) {
    if (!vis[u] && dfs_is_cyclic_wrong(u)) return true;
  }
  return false;
};


ps(vis);
```
