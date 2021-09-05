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
#define prev __prev

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

const int MOD = 1E9+7;


int main(int argc, const char **argv) {

  int m = 1000;
  vi scieve(m+1), mobius(m+1);
  for (int k = 2; k <= m; ++k) {
    if (scieve[k] || scieve[k] == -1) continue;
    for (int j = k; j <= m; j += k) {
      if (j % (k * k) == 0) scieve[j] = -1;
      else if (scieve[j] != -1) scieve[j]++;
    }
  }
  for (int k = 0; k <= m; ++k) {
    if (scieve[k] == -1) continue;
    mobius[k] = scieve[k]%2 == 0 ? 1: -1;
  }

  for (int k = 0; k <= m; ++k) {
    ps(k, mobius[k]);
  }

  return 0;
}
