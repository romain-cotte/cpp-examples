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

int main(int argc, const char **argv) {
  {
    vi a = {1, 5, 6, 10, 105};
    vi b = {8, 15, 50, 150};
    vi c;
    merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(c));
    vi exp = {1, 5, 6, 8, 10, 15, 50, 105, 150};
    assert(c == exp);
    ps(c);
  }
  {
    vi a = {1, 5, 6, 10, 105};
    vi b = {8, 15, 50, 150};
    vi c(a.size() + b.size());
    merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
    // The compare function can be specified
    // merge(a.begin(), a.end(), b.begin(), b.end(), c.begin(), [](int a, int b) {
    //   return a < b;
    // });
    vi exp = {1, 5, 6, 8, 10, 15, 50, 105, 150};
    assert(c == exp);
  }

  {
    vi v = {1, 10, 12, 50, 2, 15, 45, 56};
    //      l1         r1 l2          r2
    vi c;
    merge(v.begin(), v.begin()+4, v.begin()+4, v.end(), back_inserter(c));
    vi exp = {1, 2, 10, 12, 15, 45, 50, 56};
    assert(c == exp);
  }

  {
    vi v = {1, 10, 12, 50, 2, 15, 45, 56};
    //      l1         r1 l2          r2
    inplace_merge(v.begin(), v.begin()+4, v.end());
    vi exp = {1, 2, 10, 12, 15, 45, 50, 56};
    assert(v == exp);
  }


  return 0;
}
