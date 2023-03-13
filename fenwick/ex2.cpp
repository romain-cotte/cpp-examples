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
void _ps_continue() { pr("\n"); }
template<class Arg, class... Args> void _ps_continue(const Arg& first, const Args&... rest) {
  pr(" ", first); _ps_continue(rest...);
}
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
  pr(first); _ps_continue(rest...);
}

template<typename T> int remin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<typename T> int remax(T& a,const T& b){if(a<b){a=b;return true;}return false;}

typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;


struct Fen {
  int _n;
  vi v;
  Fen(int n): _n(n) {
    int p = 1;
    while (p <= n) {
      p = p << 1;
    }
    v.resize(p);
  }
  int lsb(int k) {
    return k&-k;
  }

  void update(int i, int value) {
    while (i <= _n) {
      v[i] += value;
      ps(i, value);
      i = i+lsb(i);
    }
  }

  int query(int k) {
    int r = 0;
    while (k) {
      r += v[k];
      k -= lsb(k);
    }
    return r;
  }
};

// process is:
// 001101 1 + 4 + 8 = 13
// 001110
// 010000
// 100000

// 001100 4 + 8 = 14

// 00011011001
// 00011011010
// 00011011100
// 00011100000
// 00100000000


int main(int argc, const char **argv) {
  int n = 20;
  Fen f(n);
  f.update(2, 1);    //  10
  f.update(3, 1);    //  11
  f.update(4, 1);    // 100
  f.update(14, 100); //  8 + 4 + 2    1110
  // ps(f.query(15));   // 1111
  return 0;
}
