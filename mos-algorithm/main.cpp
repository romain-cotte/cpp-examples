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

int block_size;
struct Query {
  int l, r, idx;
  Query(int _l, int _r, int _idx) : l(_l), r(_r), idx(_idx) {}
  bool operator<(const Query &rhs) const {
    return make_pair(l / block_size, r) <
           make_pair(rhs.l / block_size, rhs.r);
  }
};


int main(int argc, const char **argv) {
  const int n = 1'000'000;
  const int m = 100'000;

  // Tutorial said that make the block_size a const
  // improve efficienty however, in practice it's
  // equivalent 8204.429 milliseconds instead of
  // 8310.155 milliseconds
  block_size = sqrt(n) + 1;



  ps("block_size", block_size);

  uniform_int_distribution<>dist(1, 100);
  uniform_int_distribution<>dist0_n(0, n-1);

  vi a(n); vii Q(m);
  for (int i = 0; i < n; ++i) {
    a[i] = dist(gen);
  }
  for (int i = 0; i < m; ++i) {
    int l = dist0_n(gen), r = dist0_n(gen);
    if (i == 0) {
      l = 0, r = 1;
    }
    if (r < l) swap(l, r);
    Q[i] = {l, r};
  }

  clock_t t_clock = clock();
  vector<Query> qs;
  for (int i = 0; i < m; ++i) {
    qs.push_back(Query(Q[i].first, Q[i].second, i));
  }
  sort(qs.begin(), qs.end());
  vi ans(m);
  int cl = 0, cr = -1;
  ll T = 0;
  for (int i = 0; i < m; ++i) {
    Query q = qs[i];
    while (cr < q.r) {
      T += a[++cr];
    }
    while (q.r < cr) {
      T -= a[cr--];
    }
    while (cl < q.l) {
      T -= a[cl++];
    }
    while (q.l < cl) {
      T += a[--cl];
    }
    ans[q.idx] = T;
  }

  for (int q = 0; q < m; ++q) {
    ll S = 0;
    for (int i = Q[q].first; i <= Q[q].second; ++i) {
      S += a[i];
    }
    assert(S == ans[q]);
  }
  fprintf(
    stderr,
    "Time %.3f milliseconds.\n",
    ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000
  );
  return 0;
}
