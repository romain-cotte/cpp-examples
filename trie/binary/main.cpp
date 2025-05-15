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


struct Trie {
  vector<array<int, 2>> trie{{-1,-1}};
  vector<array<set<int>, 2>> indexes{};
  const int nn = 30;

  void add(ll x, int i) {
    int c = 0;
    for (int k = nn; k >= 0; --k) {
      int b = (x >> k)&1;
      if (trie[c][b] == -1) {
        trie[c][b] = trie.size();
        trie.push_back({-1, -1});
        indexes.push_back({});
      }
      indexes[c][b].insert(i);
      c = trie[c][b];
    }
  }

  void apply_xor(ll x) {
    int c = 0;
    for (int k = nn; k >= 0; --k) {
      int b = (x >> k)&1;
      if (trie[c][b] == -1) {
        trie[c][b] = trie.size();
        trie.push_back({-1, -1});
        indexes.push_back({});
      }
      indexes[c][b].insert(i);
      c = trie[c][b];
    }
  }


  void remove_from(int c) {
    if (c == -1) return;
    indexes[c][0].clear();
    indexes[c][1].clear();
    remove_from(trie[c][0]);
    remove_from(trie[c][1]);
    trie[c][0] = -1;
    trie[c][1] = -1;
  }


  vi remove_lt(ll x) {
    vi ret;
    int c = 0;
    for (int k = nn; k >= 0; --k) {
      int b = (x >> k)&1;
      if (b > 0) {
        for (int x: indexes[c][0]) ret.push_back(x);
        indexes[c][0].clear();
        remove_from(trie[c][0]);
      }
      if (trie[c][b] == -1) break;
      c = trie[c][b];
    }
    return ret;
  }

};


void solve() {
  Trie trie;

  int n; cin >> n;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    trie.add(x, i);
  }

  vi v = trie.remove_lt(5);
  vi exp = {0, 1, 2, 3, 4};
  assert(v == exp);
  ps(v);

}

int main(int argc, const char **argv) {
  solve();
  return 0;
}
