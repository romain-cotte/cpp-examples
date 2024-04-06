#include <algorithm>
#include <assert.h>
#include <bitset>
#include <chrono>
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

#define INF 2E9
#define INF64 4E18

using namespace std;

template<class T1, class T2> void pr(const pair<T1,T2>& x);
template<class T, size_t SZ> void pr(const array<T,SZ>& x);
template<class T> void pr(const vector<T>& x);
template<class T> void pr(const deque<T>& x);
template<class T, class C> void pr(const set<T,C>& x);
template<class T, class C> void pr(const multiset<T,C>& x);
template<class T1, class T2> void pr(const map<T1,T2>& x);
template<class... T> void pr(const tuple<T...>& tup);

const string COLOR_RESET = "\033[0m", GREEN = "\033[1;32m", BRIGHT_RED = "\033[1;31m", BRIGHT_CYAN = "\033[1;36m", NORMAL_CROSSED = "\033[0;9;37m", RED_BACKGROUND = "\033[1;41m", NORMAL_FAINT = "\033[0;2m";
template<class T> void pr(const T& x) { cout << GREEN << x << COLOR_RESET; }


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
typedef vector<vector<ld>> T;


random_device rd;
mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

vi perm1(int n) {
  vi v(n);
  iota(v.begin(), v.end(), 1);
  for (int i = 0; i < n; ++i) {
    uniform_int_distribution<>dist(i, n-1);
    swap(v[i], v[dist(gen)]);
  }
  return v;
}

vi perm2(int n) {
  vi v(n);
  iota(v.begin(), v.end(), 1);
  uniform_int_distribution<>dist(0, n-1);
  for (int i = 0; i < n; ++i) {
    swap(v[i], v[dist(gen)]);
  }
  return v;
}


int inv(const vi &v) {
  int n = v.size();
  int r = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
      if (v[i] > v[j]) ++r;
    }
  }
  return r;
}


T prob() {
  int n = 1000;
  T prv(n, vector<ld>(n)), nxt(n, vector<ld>(n));
  ld pmove = (ld)1/n;
  ld pstay = 1-pmove;
  for (int i = 0; i < n; ++i) {
    prv[i][i] = 1;
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      nxt[i][k] = 0;
      for (int j = 0; j < n; ++j) {
        nxt[i][k] += prv[i][j] * pmove;
        if (j != k) {
          nxt[i][j] = prv[i][j] * pstay + prv[i][k] * pmove;
        }
      }
    }
    prv = nxt;
  }
  return nxt;
}


ld mean(const vi &v) {
  int n = v.size();
  ld r = 0;
  for (int i = 0; i < n; ++i) {
    r += (i+1) * v[i];
  }
  return r;
}

ld inf(const vi &v) {
  int n = v.size();
  ld r = 0;
  for (int i = 0; i < n; ++i) {
    r += v[i] <= i;
  }
  return r;
}

ld m1 = 0, m2 = 0;
T P = prob();

void solve() {
  int n; cin >> n;
  vi a(n);
  ld p = 1;
  ld q = 1;
  for (int i = 0; i < n; ++i) {
    q /= n;
  }

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    p *= P[a[i]][i];
  }
  if (p > q) {
    cout << "BAD" << endl;
  } else {
    cout << "GOOD" << endl;
  }

  // ld m = inf(a);
  // if (m < (m1+m2)/2) {
  //   cout << (m1<m2?"GOOD":"BAD") << endl;
  // } else {
  //   cout << (m1<m2?"BAD":"GOOD") << endl;
  // }
}


int main(int argc, const char **argv) {
#ifndef DEBUG_LOCAL
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#endif
  // int C = 1000;
  // for (int i = 0; i < C; ++i) {
  //   vi v = perm1(1000);
  //   m1 += inf(v);
  //   v = perm2(1000);
  //   m2 += inf(v);
  // }
  // m1/=C; m2/=C;
  // ps(m1, m2);
  int TT; cin >> TT;
  for (int tt = 1; tt <= TT; ++tt) {
    printf("Case #%d: ", tt);
    solve();
  }

  return 0;
}

