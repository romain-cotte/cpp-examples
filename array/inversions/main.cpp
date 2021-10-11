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
template<class T> void pr(const set<T>& x);
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


template<class T>
struct Fenwick_Tree {
  vector<T> bit;
  int _n;
  Fenwick_Tree(int n): _n(n) {
    bit.resize(n+1);
  }
  inline int low_bit(int idx) { return idx&(-idx); }
  T sum(int idx) {
    T total = 0;
    int k = idx + 1;
    while (k > 0) {
      total += bit[k];
      k -= low_bit(k);
    }
    return total;
  }
  void update(int idx, int v) {
    int k = idx + 1;
    while (k < _n+1) {
      bit[k] += v;
      k += low_bit(k);
    }
  }
  T query(int l, int r) {
    return sum(r) - sum(l-1);
  }
};

int get_inversions(const vi &v) {
  int n = v.size();
  Fenwick_Tree<ll> ft(n);
  int inv = 0;
  for (int i = n-1; i >= 0; --i) {
    inv += ft.sum(v[i]);
    ft.update(v[i], 1);
  }
  return inv;
}

int main(int argc, const char **argv) {
  vi v = {1, 2, 3};
  ps(get_inversions(v));

  return 0;
}
