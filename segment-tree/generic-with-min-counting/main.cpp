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

#define INF 2E9
#define INF64 4E18

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


struct Seg_Tree {
  // WARNING: * how shoud I set the value v? += or =?
  //          * unite function +?
  using T = ll;
  function<T(T, T)> _unite_fun = [](T a, T b) {
    return a + b;
  };
  inline static void assign(ll &a, ll b) { a = b; }
  inline static void add(ll &a, ll b) { a += b; }
  inline static void set(ll &a, ll b) {
    // return assign(a, b);
    return add(a, b);
  };

  struct node {
    bool is_null = false;
    T val = 0;
    T add = 0;
    T mn = 0;
    T mn_cnt = 1;
    int l = -1, r = -1;
    node set(int _l, int _r, T v) {
      assert(_l == _r);
      // ps("set", _l, _r, v);
      l = _l; r = _r;
      Seg_Tree::set(val, v);
      Seg_Tree::set(mn, v);
      mn_cnt = 1;
      return *this;
    }
    // void apply(T v) {
    //   ps("apply", v);
    //   Seg_Tree::set(val, v);
    // }
    void apply(int l, int r, T v) {
      // ps("apply", l, r, v);
      // apply((r-l+1)*v); // when summing all values
      Seg_Tree::set(val, (r-l+1)*v);
      Seg_Tree::set(mn, v);
      // apply(v);
    }
  };
  node unite(const node &a, const node &b) {
    // printf(
    //   "unite [%d %d] and [%d %d]: %lld and %lld\n",
    //   a.l, a.r, b.l, b.r, a.val, b.val
    // );
    node r;
    r.l = a.l; r.r = b.r;
    r.val = _unite_fun(a.val, b.val);

    if (a.mn < b.mn) {
      r.mn = a.mn;
      r.mn_cnt = a.mn_cnt;
    } else if (b.mn < a.mn) {
      r.mn = b.mn;
      r.mn_cnt = b.mn_cnt;
    } else {
      r.mn = a.mn;
      r.mn_cnt = a.mn_cnt + b.mn_cnt;
    }

    return r;
  }
  int n;
  vector<T> a;
  vector<node> tree;

  Seg_Tree(int _n): n(_n) {
    a.resize(n);
    tree.resize(4 * n);
    build();
  };
  Seg_Tree(const vector<ll> &v): n(v.size()) {
    a = v;
    tree.resize(4 * n);
    build();
  }
  node build(int x, int l, int r) {
    if (l == r) { return tree[x].set(l, r, a[l]); }
    int mid = (l + r) / 2;
    node r1 = build(2 * x + 1,     l, mid);
    node r2 = build(2 * x + 2, mid+1,   r);
    return tree[x] = unite(r1, r2);
  }

  node build() { return build(0, 0, n-1); }

  void print() {
    cout << "======" << endl;
    for (int i = 0; i < n; ++i) {
      cout << query(i, i) << " ";
    }
    cout << endl;
  }

  node query(int x, int nl, int nr, int ql, int qr) {
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

  node query_node(int start_idx, int end_idx) {
    assert(start_idx <= end_idx && start_idx < n && end_idx < n);
    return query(0, 0, n-1, start_idx, end_idx);
  }

  ll query(int start_idx, int end_idx) {
    return query_node(start_idx, end_idx).val;
  }

  void update(int x, int nl, int nr, int idx, T value) {
    if (idx < nl || nr < idx) return;
    if (nl == nr) {
      Seg_Tree::set(a[idx], value);
      tree[x].set(nl, nr, value);
      return;
    }
    int mid = (nl + nr) / 2;
    update(2 * x + 1, nl   , mid, idx, value);
    update(2 * x + 2, mid+1,  nr, idx, value);
    tree[x] = unite(tree[2*x+1], tree[2*x+2]);
  }
  void update(int idx, T value) {
    assert(idx < n);
    return update(0, 0, n-1, idx, value);
  }

  void push(int x, int pl, int pr) {
    if (tree[x].add != 0) {
      tree[x].apply(pl, pr, tree[x].add);
      if (pl != pr) {
        set(tree[2*x+1].add, tree[x].add);
        set(tree[2*x+2].add, tree[x].add);
      }
      tree[x].add = 0;
    }
  }

  void update_range(int x, int pl, int pr, int l, int r, T value) {
    push(x, pl, pr);
    if (r < pl || pr < l) return;
    if (l <= pl && pr <= r) {
      tree[x].apply(pl, pr, value);
      if (pl != pr) {
        set(tree[2*x+1].add, value);
        set(tree[2*x+2].add, value);
      }
      return;
    }

    int mid = (pl + pr) / 2;
    update_range(2 * x + 1,    pl, mid, l, r, value);
    update_range(2 * x + 2, mid+1,  pr, l, r, value);
    tree[x] = unite(tree[2*x+1], tree[2*x+2]);
  }

  void update_range(int l, int r, ll value) {
    assert(l < n && r < n);
    update_range(0, 0, n-1, l, r, value);
  }
};


int main(int argc, const char **argv) {
  Seg_Tree st(8);
  vector<ll> v(8);

  auto check = [&v, &st](int i, int j) {
    ll t = 0; ll mn = INF64;
    int mn_cnt = 0;
    for (int k = i; k <= j; ++k) {
      t += v[k];
      if (v[k] < mn) {
        mn = v[k];
        mn_cnt = 1;
      } else if (mn == v[k]) {
        mn_cnt++;
      }
    }

    Seg_Tree::node no = st.query_node(i, j);
    bool ok = true;

    if (t != no.val) {
      printf("Incorrect query [%d %d] = %lld instead of %lld\n",
             i, j, no.val, t);
      assert(0);
      ok = false;
    }
    if (mn != no.mn) {
      printf("Incorrect mn [%d %d] = %lld instead of %lld\n",
             i, j, no.mn, mn);
      ok = false;
    }
    if (mn_cnt != no.mn_cnt) {
      printf("Incorrect mn_cnt [%d %d] = %lld instead of %d\n",
             i, j, no.mn_cnt, mn_cnt);
      ok = false;
    }

    return ok;
  };

  auto check_all = [&v, &st, &check]() {
    int n = v.size();
    bool ok = true;
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        ok &= check(i, j);
      }
    }

    cout << "check_all: " << (ok?"OK":"KO") << endl;
  };

  auto update = [&v, &st] (int i, ll value) {
    Seg_Tree::set(v[i], value);
    st.update(i, value);
  };

  auto update_range = [&v, &st] (int l, int r, ll value) {
    for (int i = l; i <= r; ++i) {
      Seg_Tree::set(v[i], value);
    }
    st.update_range(l, r, value);
  };

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<>dist(0, 7);
  for (int i = 0; i < 15; ++i) {
    int l = dist(gen), r = dist(gen);
    if (r < l) swap(l, r);
    update_range(l, r, i%2?+1:-1);
    st.print();
    cout << "mn_cnt: " << st.query_node(0, 7).mn_cnt << endl;
    check_all();
  }

  cout << "Everything is OK" << endl;

  return 0;
}
