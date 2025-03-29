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

#ifdef DEBUG_LOCAL
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

struct T {
  int i, j; ld d;
};


ll sq(ll x) {
  return x * x;
}

void solve() {
  int n; cin >> n;
  vector<array<int, 3>> v;
  for (int i = 0; i < n; ++i) {
    int x, y; cin >> x >> y;
    v.push_back({x, y, i});
  }

  auto euc_dist = [&](int i, int j) {
    return sqrtl(sq(v[i][0]-v[j][0])+sq(v[i][1]-v[j][1]));
  };
  // ld H = INF64;
  // int ai, aj;
  // for (int i = 0; i < n; ++i) {
  //   for (int j = i+1; j < n; ++j) {
  //     if (remin(H, euc_dist(i, j))) {
  //       ai = i; aj = j;
  //     }
  //   }
  // }

  sort(v.begin(), v.end());

  // auto man_dist = [&](int i, int j) {
  //   return abs(v[i].first-v[j].first)+abs(v[i].second-v[j].second);
  // };

  function<T(int,int)> f;
  f = [&](int l, int r) {
    if (l == r) return T{l, r, (ld)1E18};
    if (r == l+1) return T{l, r, euc_dist(l, r)};
    int m = (l+r)/2;
    T L = f(l, m), R = f(m+1, r);
    int ri, rj; ld h;
    if (L.d < R.d) {
      h = L.d;
      ri = L.i; rj = L.j;
    } else {
      h = R.d;
      ri = R.i; rj = R.j;
    }

    // [v[m].first-h, v[m].first+h]
    vector<int> B = {m};
    for (int i = 1; m-i>=l; ++i) {
      if (v[m][0]-v[m-i][0] <= h) {
        B.push_back(m-i);
      } else break;
    }
    for (int i = 1; m+i < n && m+i <= r; ++i) {
      if (v[m+i][0] - v[m][0] <= h) {
        B.push_back(m+i);
      } else break;
    }
    sort(B.begin(), B.end(), [&](int i, int j) {
      return v[i][1] < v[j][1];
    });
    int start = 0;
    for (int i = 1; i < B.size(); ++i) {
      int t = B[i];
      for (int j = start; j < i; ++j) {
        int s = B[j];
        if (v[t][1] - v[s][1] > h) ++start;
        if (remin(h, euc_dist(s, t))) {
          ri = s; rj = t;
        }
      }
    }
    return T{ri, rj, h};
  };

  T t = f(0, n-1);
  // assert(abs(H-t.d) < 1E-6);

  int a = min(v[t.i][2], v[t.j][2]);
  int b = max(v[t.i][2], v[t.j][2]);

  printf("%d %d %.6Lf\n", a, b, t.d);
}


int main(int argc, const char **argv) {
#ifndef DEBUG_LOCAL
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#endif
  solve();
  return 0;
}
