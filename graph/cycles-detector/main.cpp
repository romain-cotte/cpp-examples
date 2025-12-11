/**
 * Cycles detector
 */
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
  int n = 5;
  // cin >> n >> m;
  vi vis(n+1);
  vi rec(n+1);
  vvi G(n+1);

  function<bool(int)> dfs_is_cyclic;
  dfs_is_cyclic = [&](int u) {
    if (vis[u]) return false;
    vis[u] = 1;
    rec[u] = 1;
    for (int v: G[u]) {
      ps(u, "->", v);
      if (rec[v]) return true;
      if (!vis[v] && dfs_is_cyclic(v)) return true;
    }
    rec[u] = 0;
    return false;
  };
  auto is_cyclic = [&]() {
    for (int u = 1; u <= n; ++u) {
      if (!vis[u]) {
        if (dfs_is_cyclic(u)) return true;
      }
    }
    return false;
  };

  int cookie = 1;

  function<bool(int)> dfs_is_cyclic_wrong;
  dfs_is_cyclic_wrong = [&](int u) {
    vis[u] = cookie;
    for (int v: G[u]) {
      if (vis[v] == cookie) return true;
      if (!vis[v]) {
        if (dfs_is_cyclic_wrong(v)) return true;
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


  G[1] = {2, 3};
  G[2] = {5};
  G[3] = {5};
  G[4] = {};
  G[5] = {};
  ps(is_cyclic(), is_cyclic_wrong());


  return 0;
}
