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

int n;


int binary_search(const vi &v, int k) {
  int l = 0, r = v.size()-1;
  while (l < r) {
    int m = (l+r+1)/2;
    // ps(l, r, m);
    if (v[m] <= k) { // last index lower or equal to k
      l = m;
    } else {
      r = m-1;
    }
  }
  return l;
}

// OR
int binary_search2(const vi &v, int k) {
  int l = 0, r = v.size()-1;
  while (l < r) {
    int m = (l+r)/2;
    // ps(l, r, m);
    if (v[m] < k) { // first index greater or equal to k
      l = m + 1;
    } else {
      r = m;
    }
  }
  return l;
}


int main(int argc, const char **argv) {
  vi v = {1, 2, 3, 4, 5, 6, 7, 8, 10, 15, 100};

  for (int x = v[0]; x <= v.back(); ++x) {
    ps("===", x);
    int i = binary_search(v, x);
    int j = binary_search2(v, x);
    ps(x, i, j);
    assert(i <= j);
  }

  /**
   * When l < 0 and r > 0, you need to be very careful because
   * if you do (l+r)/2 when l+r < 0, the rounding is incorrect!
   */

  for (int x = -10; x <= 10; ++x) {
    int l = -10, r = 10;
    while (l < r) {
      int m = l+(r-l+1)/2;
      if (m <= x) {
        l = m;
      } else {
        r = m-1;
      }
    }
    ps(x, l);
    assert(l == x);
  }



  return 0;
}
