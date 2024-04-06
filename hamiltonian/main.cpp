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

const string COLOR_RESET = "\033[0m", GREEN = "\033[1;32m";
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

int B(int k, int i) {
  return k >> i & 1;
}

void solve() {
  int k, n, m; cin >> k;
  string s; cin >> s;
  n = s.size();
  m = n/k;
  // vi p(k);
  // iota(p.begin(), p.end(), 0);
  // auto f = [&](const string &s) {
  //   int ret = 1;
  //   for (int i = 1; i < n; ++i) {
  //     if (s[i] != s[i-1]) ++ret;
  //   }
  //   return ret;
  // };

  // int ans = INF;
  // do {
  //   string t = s;
  //   for (int i = 0; i < m; ++i) {
  //     for (int j = 0; j < k; ++j) {
  //       t[i*k+j] = s[i*k+p[j]];
  //     }
  //   }
  //   remin(ans, f(t));
  // } while (next_permutation(p.begin(), p.end()));

  vector<vector<int>> G(k), H(k);
  for (int i = 0; i < k; ++i) {
    G[i].resize(k);
    H[i].resize(k);
  }

  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      if (i == j) continue;
      int w = 0, z = 0;
      for (int l = 0; l < m; ++l) {
        if (s[l*k+i] != s[l*k+j]) ++w;
        if (l < m-1) {
          if (s[l*k+i] != s[(l+1)*k+j]) ++z;
        }
      }
      G[i][j] = w;
      H[i][j] = z;
    }
  }

  map<vi, int> mp_h;
  function<int(vi)> hamiltonian;
  hamiltonian = [&](const vi &p) {
    if (mp_h.count(p) == 1) return mp_h[p];
    int &ret = mp_h[p];
    if (p.size() == k) {
      for (int i = 1; i < k; ++i) {
        ret += G[p[i-1]][p[i]];
      }
      ret += H[p[0]][p[k-1]];
      return ret;
    }
    vi pre(k);
    ret = INF;
    for (int x: p) pre[x] = 1;
    for (int i = 0; i < k; ++i) {
      if (pre[i] == 0) {
        vi cp = p; cp.push_back(i);
        remin(ret, hamiltonian(cp));
        // if (cp.size() == k) {
        //   ps(ret, cp);
        // }
      }
    }
    return ret;
  };


  // vi path; int r = hamiltonian(path)+1;
  // cout << r << endl;

  clock_t t_clock = clock();



  vvi dp(1 << k, vi(k, -1));

  function<int(int,int,int)> F;
  F = [&](int A, int i, int s) { // i is necessarily in A
    assert(B(A, i));
    int &ret = dp[A][i];
    if (ret != -1) return ret;
    ret = INF;
    if (A == 1 << i) {
      return ret = H[i][s];
    }
    for (int j = 0; j < k; ++j) {
      if (i == j) continue;
      // HERE IS THE DIFFICULTY:
      // from i to j then A \ i to s AND NOT A \ j !!
      if (B(A, j)) {
        remin(ret, G[i][j] + F(A - (1 << i), j, s));
      }
    }
    return ret;
  };

  int ans = INF;
  for (int S = 0; S < k; ++S) {
    dp.assign(1 << k, vi(k, -1));
    remin(ans, 1+F((1 << k) - 1, S, S));
  }

  ps("Elapsed time",
     ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000,
     "milliseconds.");
  t_clock = clock();


  int ans2 = INF;
  for (int s = 0; s < k; ++s) {
    dp.assign(1 << k, vi(k, INF));
    for (int i = 0; i < k; ++i) {
      dp[1<<i][i] = H[i][s];
    }
    vvi v(k+1);
    for (int i = 1; i < 1 << k; ++i) {
      v[__builtin_popcount(i)].push_back(i);
    }

    for (int i = 2; i <= k; ++i) {
      for (int A: v[i]) {
        for (int x = 0; x < k; ++x) {
          if (B(A, x)) {
            for (int j = 0; j < k; ++j) {
              if (B(A, j)) {
                assert(dp[A-(1<<x)][j] != -1);
                remin(dp[A][x], G[x][j] + dp[A-(1<<x)][j]);
              }
            }
          }
        }
      }
    }
    remin(ans2, 1+dp[(1<<k)-1][s]);
  }

  ps("Elapsed time",
     ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000,
     "milliseconds.");

  ps(ans, ans2);

  assert(ans == ans2);

  // ps(ans, r);
  // assert(ans == r);
  cout << ans << endl;
}


int main(int argc, const char **argv) {
#ifndef DEBUG_LOCAL
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  clock_t t_clock = clock();
#endif
  int TT; cin >> TT;
  for (int tt = 1; tt <= TT; ++tt) {
    cout << "Case #" << tt << ": ";
    solve();
  }
#ifndef DEBUG_LOCAL
  ps("Elapsed time",
     ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000,
     "milliseconds.");
#endif
  return 0;
}
