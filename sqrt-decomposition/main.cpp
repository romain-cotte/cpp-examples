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

/**
 * SQRT decomposition, see https://cp-algorithms.com/data_structures/sqrt_decomposition.html
 */
random_device rd;
mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, const char **argv) {
  const int n = 20;
  int s = sqrt(n) + 1;
  uniform_int_distribution<>dist(1, 100);

  ps("n", n, "s", s);
  vi a(n);
  vi b(s);
  for (int i = 0; i < n; ++i) {
    a[i] = dist(gen);
  }

  for (int i = 0; i < n; ++i) {
    b[i/s] += a[i];
  }
  ps(a);
  ps(b);

  auto sum = [&](int l, int r) {
    int S = 0, T = 0, U = 0;
    for (int i = l; i <= r; ++i) {
      S += a[i];
    }
    int lb = (l+s-1) / s;
    int rb = r / s;

    if (lb >= rb) {
      for (int i = l; i <= r; ++i) {
        T += a[i];
      }
    } else {
      for (int i = l; i < s * lb; ++i) {
        T += a[i];
      }
      for (int i = lb; i < rb; ++i) {
        T += b[i];
      }
      for (int i = s * rb; i <= r; ++i) {
        T += a[i];
      }
    }
    if (S != T) {
      ps(l, r, lb, rb, S, T);
    }
    assert(S == T);

    // Another simpler way to compute the indexes
    // but divisions are more expensive
    for (int i = l; i <= r; ) {
      if (i % s == 0 && i+s-1 <= r) {
        U += b[i/s];
        i += s;
      } else {
        U += a[i];
        ++i;
      }
    }
    if (S != U) {
      ps(l, r, lb, rb, S, U);
    }
    assert(S == U);

    // Solution 3
    T = 0;
    lb = l / s, rb = r / s;
    if (lb == rb) {
      for (int i = l; i <= r; ++i) {
        T += a[i];
      }
    } else {
      for (int i = l; i < s * (lb+1); ++i) {
        T += a[i];
      }
      for (int i = lb+1; i <= rb-1; ++i) {
        T += b[i];
      }
      for (int i = s*rb; i <= r; ++i) {
        T += a[i];
      }
    }
    assert(S == T);

    return S;
  };


  for (int l = 0; l < n; ++l) {
    for (int r = l; r < n; ++r) {
      sum(l, r);
    }
  }

  return 0;
}
