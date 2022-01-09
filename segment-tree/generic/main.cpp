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


/**
 * Complexity: construction: O(n), query: O(log(n))
 *       [1;6]
 *      /     \
 * [1;3]      [4;6]
 *   |  \
 * [1;2] [2;3] ...
 *   |  \
 * [1;1] [2;2]
 *
 * Pointers are shrinking, we keep as long as intersection is not null
 * query(3, 5): [1;6] -> [1;3] & [4;6]
 */
struct seg_tree {
  struct node {
    bool is_null = false;
    int mn = 0;
    int add = 0;
    int l = -1, r = -1;
    node set(int _l, int _r, int v) {
      l = _l; r = _r;
      mn = v;
      return *this;
    }
    void apply(int v) {
      mn += v;
    }
  };
  node unite(const node &a, const node &b) {
    printf(
      "unite [%d %d] and [%d %d]: %d and %d\n",
      a.l, a.r, b.l, b.r, a.mn, b.mn
    );
    node r;
    r.l = a.l; r.r = b.r;
    r.mn = min(a.mn, b.mn);
    return r;
  }

  int n;
  vi a;
  vector<node> tree;

  seg_tree(const vi &v): n(v.size()) {
    a = v;
    tree.resize(2 * n - 1);
    build();
  }

  node build(int x, int l, int r) {
    assert(x < 2*n);
    if (l == r) { return tree[x].set(l, r, a[l]); }
    int mid = (l + r) / 2;
    node r1 = build(2 * x + 1,     l, mid);
    node r2 = build(2 * x + 2, mid+1,  r);
    return tree[x] = unite(r1, r2);
  }

  node build() { return build(0, 0, n-1); }

  node query(int x, int nl, int nr, int ql, int qr) {
    assert(x < 2*n);
    push(x, nl, nr);
    if (ql <= nl && nr <= qr) return tree[x];
    if (qr < nl || nr < ql) return { true };
    int mid = (nl + nr) / 2;
    node q1 = query(2 * x + 1, nl   , mid, ql, qr);
    node q2 = query(2 * x + 2, mid+1,  nr, ql, qr);
    if (q1.is_null) return q2;
    if (q2.is_null) return q1;
    return unite(q1, q2);
  }
  node query(int start_idx, int end_idx) {
    return query(0, 0, n-1, start_idx, end_idx);
  }

  void update(int x, int nl, int nr, int idx, ll value) {
    if (idx < nl || nr < idx) return;
    if (nl == nr) {
      a[idx] = value;
      tree[x].set(nl, nr, value);
      return;
    }
    int mid = (nl + nr) / 2;
    update(2 * x + 1, nl   , mid, idx, value);
    update(2 * x + 2, mid+1,  nr, idx, value);
    tree[x] = unite(tree[2*x+1], tree[2*x+2]);
  }
  void update(int idx, ll value) { return update(0, 0, n-1, idx, value); }

  void push(int x, int pl, int pr) {
    if (tree[x].add != 0) {
      tree[x].apply(tree[x].add); // += (pr-pl+1) * lazy_tree[x];
      if (pl != pr) {
        tree[2*x+1].add += tree[x].add; // += -> =
        tree[2*x+2].add += tree[x].add; // += -> =
      }
      tree[x].add = 0;
    }
  }

  void update_range(int x, int pl, int pr, int l, int r, ll value) {
    push(x, pl, pr);
    if (r < pl || pr < l) return;
    if (l <= pl && pr <= r) {
      tree[x].apply(value); // += (pr-pl+1)*value; // tree[x] = value;
      if (pl != pr) {
        tree[2*x+1].add += value; // lazy_tree[2*x+1] = value
        tree[2*x+2].add += value; // lazy_tree[2*x+2] = value
      }
      return;
    }

    int mid = (pl + pr) / 2;
    update_range(2 * x + 1,    pl, mid, l, r, value);
    update_range(2 * x + 2, mid+1,  pr, l, r, value);
    tree[x] = unite(tree[2*x+1], tree[2*x+2]);
  }

  void update_range(int l, int r, ll value) {
    update_range(0, 0, n-1, l, r, value);
  }
};


int main(int argc, const char **argv) {

  vi v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  seg_tree st(v);
  ps("---");
  ps(st.query(0, 0).mn);
  ps(st.query(0, 1).mn);
  ps(st.query(0, 2).mn);
  ps(st.query(0, 3).mn);
  ps(st.query(0, 4).mn);
  ps(st.query(4, 8).mn);

  st.update_range(0, 4, +100);
  ps(st.query(0, 0).mn);
  ps(st.query(1, 1).mn);
  ps(st.query(2, 2).mn);
  ps(st.query(3, 3).mn);
  ps(st.query(4, 4).mn);
  ps(st.query(5, 5).mn);
  ps(st.query(6, 6).mn);
  ps(st.query(0, 8).mn);


  return 0;
}
