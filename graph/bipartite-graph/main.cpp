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
#include "sol.cpp"

#define INF 1E9
#define INF64 2E18

using namespace std;

template<class T1, class T2> void pr(const pair<T1,T2>& x);
template<class T, size_t SZ> void pr(const array<T,SZ>& x);
template<class T> void pr(const vector<T>& x);
template<class T> void pr(const set<T>& x);
template<class T> void pr(const multiset<T>& x);
template<class T1, class T2> void pr(const map<T1,T2>& x);
template<class T1, class T2> void pr(const map<T1,T2>& x);
template<class... T> void pr(const tuple<T...>& tup);

template<class T> void pr(const T& x) { cout << x; }
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
template<class T> void pr(const set<T>& x) { prContain(x); }
template<class T> void pr(const multiset<T>& x) { prContain(x); }
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
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
  pr(first," "); ps(rest...);
}

template<typename T> int remin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<typename T> int remax(T& a,const T& b){if(b>a){a=b;return true;}return false;}

typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n, m;
vector<vi> G;
vector<int> vis, parent;
int cookie;

bool matching(int u) {
  if (vis[u] == cookie) return false;
  vis[u] = cookie;
  for (int v: G[u]) {
    if (parent[v] == -1) {
      parent[v] = u;
      return true;
    }
    if (matching(parent[v])) {
      parent[v] = u;
      return true;
    }
  }
  return false;
}

int matches() {
  int ans = 0;
  vis.assign(n, false);
  parent.assign(n, -1);
  for (int u = 0; u < n; ++u) {
    ++cookie;
    ans += matching(u);
  }
  return ans;
}


void solve() {
  scanf("%d%d", &n, &m);
  G.assign(n, {});
  for (int i = 0; i < m; ++i) {
    int u, v; scanf("%d%d", &u, &v);
    G[u].push_back(v);
  }
  int r = sol_matches(G);
  int s = matches();
  assert(r == s);
  printf("%d\n", r);
}

int main(int argc, const char **argv) {
  clock_t t_clock = clock();
  int TT; scanf("%d", &TT);
  for (int tt = 1; tt <= TT; ++tt) {
    printf("Case #%d: ", tt);
    solve();
  }
  fprintf(
    stderr,
    "Elapsed time %.3f milliseconds.\n",
    ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000
  );
  return 0;
}
