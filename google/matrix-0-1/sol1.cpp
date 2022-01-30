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

#define INF 1E9
#define INF64 2E18

using namespace std;

template<class T1, class T2> void pr(const pair<T1,T2>& x);
template<class T, size_t SZ> void pr(const array<T,SZ>& x);
template<class T> void pr(const vector<T>& x);
template<class T, class C> void pr(const set<T,C>& x);
template<class T, class C> void pr(const multiset<T,C>& x);
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

void solve() {
  int R, C; scanf("%d%d", &R, &C);
  vector<vi> mat(R, vi(C));
  vector<vi> pref(R+1, vi(C+1));

  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      scanf("%d", &mat[r][c]);
    }
  }

  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      pref[r+1][c+1] = pref[r][c+1] + pref[r+1][c] - pref[r][c];
      pref[r+1][c+1] += mat[r][c] == 1;
    }
  }

  auto get = [&pref](int r1, int c1, int r2, int c2) {
    return pref[r2+1][c2+1] - pref[r2+1][c1] - pref[r1][c2+1] + pref[r1][c1];
  };

  int ans = 0;
  vi vans;
  for (int r1 = 0; r1 < R; ++r1) {
    for (int c1 = 0; c1 < C; ++c1) {
      for (int r2 = r1; r2 < R; ++r2) {
        for (int c2 = c1; c2 < C; ++c2) {
          int r = get(r1, c1, r2, c2);
          if (r == (r2-r1+1) * (c2-c1+1)) {
            if (remax(ans, get(r1, c1, r2, c2))) {
              vans = {r1, c1, r2, c2};
            }
          }
        }
      }
    }
  }
  ps(ans, vans);
}


int main(int argc, const char **argv) {
  solve();
  return 0;
}
