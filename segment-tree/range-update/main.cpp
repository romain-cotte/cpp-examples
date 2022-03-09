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

int n;
const int NN = 1000;
vi a;
ll seg_tree[4 * NN];
ll lazy_st[4 * NN];

inline ll op(ll a, ll b) {
  return max(a, b);
}
/**
 * Construct the segment tree from the array a, be careful, size of the segment
 * tree should be 4 * size of a.
 * The real value is while (sz < N) sz *= 2; seg_tree.resize(sz * 2);
 * You should call build_seg_tree(0, 0, n-1);
 * where N is the size of array a
 * Complexity: construction: O(n), query: O(log(n))
 */
ll _build_seg_tree(int node, int lh, int rh) {
  n = a.size();
  if (lh == rh) {
    return seg_tree[node] = a[lh];
  }
  int mid = (lh + rh) / 2;
  ll r1 = _build_seg_tree(2 * node + 1,    lh, mid);
  ll r2 = _build_seg_tree(2 * node + 2, mid+1,  rh);
  return seg_tree[node] = op(r1, r2);
}
ll build_seg_tree() { _build_seg_tree(0, 0, a.size()-1); }


void prop_lazy(int node, int pl, int pr) {
  if (lazy_st[node] != 0) {
    seg_tree[node] += (pr-pl+1) * lazy_st[node];
    if (pl != pr) {
      lazy_st[2*node+1] += lazy_st[node];
      lazy_st[2*node+2] += lazy_st[node];
    }
    lazy_st[node] = 0;
  }
}

/**
 * Query a segment of the array
 * You should call query(0, 0, n-1, start_idx, end_idx);
 * it will give the maximum value between indexes start_idx and end_idx included
 */
ll _query(int node, int nl, int nr, int ql, int qr) {
  prop_lazy(node, nl, nr);
  if (ql <= nl && nr <= qr) return seg_tree[node];
  if (qr < nl || nr < ql) return -1;
  int mid = (nl + nr) / 2;
  ll q1 = _query(2 * node + 1, nl   , mid, ql, qr);
  ll q2 = _query(2 * node + 2, mid+1,  nr, ql, qr);
  if (q1 == -1) return q2;
  if (q2 == -1) return q1;
  return op(q1, q2);
}
ll query(int start_idx, int end_idx) {
  return _query(0, 0, n-1, start_idx, end_idx);
}


/**
 * Update the value of a at idx and update the seg_tree accordingly
 * You should call update(0, 0, n-1, idx, value);
 * then a[idx] = value
 */
void _update(int node, int nl, int nr, int idx, int value) {
  if (idx < nl || nr < idx) return;
  if (nl == nr) {
    seg_tree[node] = /*a[idx] =*/ value;
    return;
  }
  int mid = (nl + nr) / 2;
  _update(2 * node + 1, nl   , mid, idx, value);
  _update(2 * node + 2, mid+1,  nr, idx, value);
  seg_tree[node] = op(seg_tree[2*node+1], seg_tree[2*node+2]);
}
void update(int idx, int value) { return _update(0, 0, n, idx, value); }

void _update_range(int node, int pl, int pr, int l, int r, int value) {
  prop_lazy(node, pl, pr);
  if (r < pl || pr < l) return;
  if (pl <= l && r <= pr) {
    seg_tree[node] += (r-l+1) * value;
    if (l != r) {
      lazy_st[2*node+1] += value;
      lazy_st[2*node+2] += value;
    }
    return;
  }

  int mid = (l+r)/2;
  _update_range(2*node+1, pl, mid, l, r, value);
  _update_range(2*node+2, mid+1, pr, l, r, value);
  seg_tree[node] = seg_tree[2*node+1] + seg_tree[2*node+2];
  return;
}

int main(int argc, const char **argv) {
  a.assign({ 1, 2, 3, 4, 5, 6, 1, 9, 2});
  ps("a", a);
  n = a.size();
  build_seg_tree();

  _update_range(0, 0, n-1, 1, n-2, 100);
  for (int i = 0; i < n; ++i) {
    printf("%lld ", lazy_st[i]);
  }
  printf("\n");

  for (int i = 0; i < n; ++i) {
    ps(i, query(i, i), a[i]);
  }

  for (int i = 0; i < n; ++i) {
    printf("%lld ", lazy_st[i]);
  }
  printf("\n");
  return 0;
}
