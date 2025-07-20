#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>

#define INF 1 << 30      //          1073741824 1E9
#define INF64 1LL << 60  // 1152921504606846976 1E18

using namespace std;

template<class T1, class T2> void pr(const pair<T1,T2>& x);
template<class T, size_t SZ> void pr(const array<T,SZ>& x);
template<class T> void pr(const vector<T>& x);
template<class T> void pr(const deque<T>& x);
template<class T, class C> void pr(const set<T,C>& x);
template<class T, class C> void pr(const multiset<T,C>& x);
template<class T1, class T2> void pr(const map<T1,T2>& x);
template<class... T> void pr(const tuple<T...>& tup);

const string COLOR_RESET = "\033[0m", GREEN = "\033[1;32m";
template<class T> void pr(const T& x) {
#if COLOR == true
  cout << GREEN << x << COLOR_RESET;
#else
  cout << x;
#endif
}

template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
  pr(first); pr(rest...);
}
template<class T1, class T2> void pr(const pair<T1,T2>& x) {
  pr("{",x.first,", ",x.second,"}");
}
template<class T> void prContain(const T& x) {
  pr("{");bool fst = 1; for(auto &a: x) pr(!fst?", ":"",a), fst = 0;pr("}");
}
template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
template<class T> void pr(const vector<T>& x) { prContain(x); }
template<class T> void pr(const deque<T>& x) { prContain(x); }
template<class T, class C> void pr(const set<T,C>& x) { prContain(x); }
template<class T, class C> void pr(const multiset<T,C>& x) { prContain(x); }
template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }

template<class T, size_t... I>
void pr(const T& tup, index_sequence<I...>) {
  pr("("); (..., (cout << (I == 0? "" : ", ") << get<I>(tup))); pr(")");
}
template<class... T>
void pr (const tuple<T...>& tup) {
  pr(tup, make_index_sequence<sizeof...(T)>());
}
void ps() { pr("\n"); }
void _ps_continue() { pr("\n"); }
template<class Arg, class... Args> void _ps_continue(const Arg& first, const Args&... rest) {
  pr(" ", first); _ps_continue(rest...);
}

#if defined(DEBUG_LOCAL) && DEBUG_LOCAL
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
  pr(first); _ps_continue(rest...);
}
#else
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {}
#endif

template<typename T> int remin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<typename T> int remax(T& a,const T& b){if(a<b){a=b;return true;}return false;}

typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;


int main(int argc, const char **argv) {
#ifndef DEBUG_LOCAL
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#endif
  clock_t t_clock = clock();
  int n; cin >> n;
  vvi G(n+1); vi depth(n+1);

  int k = 0;
  {
    int p = 1;
    while (p < n) {
      ++k; p <<= 1;
    }
  }
  ps(k);
  vvi parent(n+1, vi(k+1));

  parent[1][0] = 1;
  for (int i = 0; i < n-1; ++i) {
    int u, v; cin >> u >> v;
    G[u].push_back(v);
    parent[v][0] = u;
  }

  function<void(int,int)> dfs;
  dfs = [&](int u, int d) {
    depth[u] = d;
    for (int v: G[u]) dfs(v, d+1);
  };
  dfs(1, 0);

  for (int j = 1; j <= k; ++j) {
    for (int i = 1; i <= n; ++i) {
      parent[i][j] = parent[parent[i][j-1]][j-1];
    }
  }


  ps(parent[14][0]);
  ps(parent[14][1]);
  ps(parent[14][2]);
  ps(parent[14][3]);


  auto lca = [&](int u, int v) {
    if (depth[v] < depth[u]) swap(u, v);
    int d = depth[v] - depth[u];

    for (int i = k; i >= 0; --i) {
      if ((d >> i)&1) {
        v = parent[v][i];
      }
    }
    for (int i = k; i >= 0; --i) {
      if (parent[u][i] != parent[v][i]) {
        u = parent[u][i];
        v = parent[v][i];
      }
    }
    if (u != v) {
      return parent[u][0];
    }
    return u;
  };

  auto lca_naive = [&](int u, int v) {
    set<int> st = {u};
    while (u != 1) {
      u = parent[u][0];
      st.insert(u);
    }
    while (true) {
      if (st.find(v) != st.end()) {
        return v;
      }
      v = parent[v][0];
    }

    return -1;
  };

  for (int u = 1; u <= n; ++u) {
    for (int v = 1; v <= n; ++v) {
      assert(lca(u, v) == lca_naive(u, v));
      ps(u, v, lca(u, v));
    }
  }

  fprintf(
    stderr,
    "Time %.3f milliseconds.\n",
    ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000
  );

  return 0;
}
