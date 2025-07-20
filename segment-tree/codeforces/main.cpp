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

const int N = 100;
vi a;

struct Node {
  int mn;
};

struct SegTree {
  // STARTING INDEX FOR u should be 1!
  Node t[N<<2];
  #define lc(u) (u<<1)
  #define rc(u) (u<<1|1)
  void pushup(int u, int l, int r) {
    // int mid = (l + r) >> 1;
    t[u].mn = min(t[lc(u)].mn, t[rc(u)].mn);
  }
  void build(int u, int l, int r) {
    if (l == r) {
      t[u].mn = a[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(lc(u), l, mid);
    build(rc(u), mid+1, r);
    pushup(u, l, r);
  }
  void modify(int u, int l, int r, int ql, int qr, int va) {
    if(l == r) {
      t[u].mn += va;
      return;
    }
    int mid = (l + r) >> 1;
    if(ql <= mid) modify(lc(u), l, mid, ql, qr, va);
    if(qr > mid) modify(rc(u), mid+1, r, ql, qr, va);
    pushup(u, l, r);
  }
  int query(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
      ps(":", u, l, r, ql, qr, t[u].mn);
      return t[u].mn;
    }
    int mid = (l+r) >> 1;
    if (qr <= mid) return query(lc(u), l, mid, ql, qr);
    if (ql > mid) return query(rc(u), mid+1, r, ql, qr);

    return min(
      query(lc(u), l, mid, ql, qr),
      query(rc(u), mid+1, r, ql, qr)
    );
  }

  #undef lc
  #undef rc
} sgt;



int main(int argc, const char **argv) {
#ifndef DEBUG_LOCAL
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#endif

  a = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  SegTree st;
  st.build(1, 0, 8);

  auto check = [&st](int i, int j) {
    ll t = INF;
    for (int k = i; k <= j; ++k) {
      // t += a[k];
      remin(t, (ll)a[k]);
    }
    ll r = st.query(1, 0, 8, i, j);
    if (t != r) {
      printf("Incorrect query %d %d = %lld instead of %lld\n",
             i, j, r, t);
      assert(0);
    }
  };
  auto check_all = [&st, &check]() {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        check(i, j);
      }
    }
  };

  check_all();

  {
    int l = 1, r = 7;
    st.modify(1, 0, 8, 1, 7, +3);
    for (int k = l; k <= r; ++k) {
      a[k] += 3;
    }
  }
  check_all();


  return 0;
}
