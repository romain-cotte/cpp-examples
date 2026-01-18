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

int nb(int i, int di) {
  int r = 0;
  while (i) {
    r += (i%10) == di;
    i /= 10;
  }
  return r;
}


void solve() {
  int k, d; cin >> k >> d;
  ll a, b; cin >> a >> b;
  vi va, vb;
  {
    int ta = a, tb = b;
    while (ta | tb) {
      va.push_back(ta%10);
      ta /= 10;
      vb.push_back(tb%10);
      tb /= 10;
    }
  }
  va.push_back(0);
  vb.push_back(0);
  reverse(va.begin(), va.end());
  reverse(vb.begin(), vb.end());
  ps(vb);
  ps(va);
  int s = va.size();
  ll dp[20][2][2][20];
  memset(dp, -1, sizeof(dp));
  // for (int i = 0; i < 20; ++i) {
  //   for (int j = 0; j < 10; ++j) {
  //     for (int k = 0; k < 1; ++k) {
  //       for (int l = 0; l < 1; ++l) {
  //         ps(dp[i][j][k][l]);
  //       }
  //     }
  //   }
  // }
  function<ll(int,bool,bool,int)> f;
  f = [&](int i, bool lo, bool hi, int t) {
    if (t > k) return 0LL;
    if (i == s) return (ll)(t == k);
    ll &r = dp[i][lo][hi][t];
    if (r != -1) return r;
    r = 0;
    int from = 0, to = 9;
    if (lo) remax(from, va[i]);
    if (hi) remin(to, vb[i]);
    for (int di = from; di <= to; ++di) {
      r += f(i+1, lo&(di==from), hi&(di==to), t+(di==d));
    }
    return r;
  };
  cout << f(0, 1, 1, 0) << endl;
  int ans = 0;
  for (int i = a; i <= b; ++i) {
    ans += nb(i, d) == k;
  }
  cout << ans << endl;
}




int main(int argc, const char **argv) {
#ifndef DEBUG_LOCAL
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#endif
  int TT; cin >> TT;
  for (int tt = 1; tt <= TT; ++tt) {
    ps("Case#", tt);
    solve();
  }
  return 0;
}
