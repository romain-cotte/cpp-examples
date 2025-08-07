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

const int NN = 1E5+5;
int c[NN];
int n = 10000;


template<class T = ll>
struct Fenwick_Tree {
  vector<T> bit;
  int n;
  ll total = 0;
  Fenwick_Tree() {}
  Fenwick_Tree(int _n): n(_n) {
    bit.resize(n+2);
  }
  inline int low_bit(int idx) { return idx&(-idx); }
  T sum(int idx) {
    T ret = 0;
    ++idx;
    for (int k = idx; k>0; k-=low_bit(k)) {
      ret += bit[k];
    }
    return ret;
  }
  void update(int idx, int v) {
    total += v;
    assert(idx >= 0 && idx <= n);
    ++idx;
    for (int k = idx; k < n+2; k+=low_bit(k)) {
      bit[k] += v;
    }
  }
  T query(int l, int r) {
    assert(r <= n);
    assert(l <= r);
    return sum(r) - sum(l-1);
  }
  T query_lte(int x) {
    if (x < 0) return 0;
    return query(0, x);
  }
  T query_gte(int x) {
    return total - query_lte(x-1);
  }
  int find_kth(int x) {
    // smallest k that query_lte(k) >= x
    int p = 0;
    for (int i = 20; i >= 0; --i) {
      if (p+(1<<i) <= n+1 && bit[p+(1<<i)]<x) {
        x -= bit[p+(1<<i)];
        p += 1 << i;
      }
    }
    return p;
  }
};


int main(int argc, const char **argv) {
#ifndef DEBUG_LOCAL
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#endif

  int n = 200;


  Fenwick_Tree<ll> ft(n);

  ft.update(10, 1);
  ft.update(11, 1);
  ft.update(15, 1);
  ft.update(100, 10);
  ft.update(150, 1);
  ft.update(200, 1);

  for (int i = 0; i < 20; ++i) {
    ps(i, ft.find_kth(i));
  }

  // modify(10, 100);
  // modify(11, 100);
  // modify(15, 100);
  // cout << find(20) << endl;

  return 0;
}
