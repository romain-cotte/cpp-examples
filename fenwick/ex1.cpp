#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>
#include <unistd.h>

#define SZ(x) (int)(x.size())
#define F0(i,n) for(int i=0;i<n;i++)
#define F1(i,n) for(int i=1;i<=n;i++)
#define FI(i,n) for(int i=0;i<=n;i++)
#define TR(x) cout << #x << " = " << x << endl
#define FE(k) get<0>(k)
#define SE(k) get<1>(k)
#define TH(k) get<2>(k)
#define TRAV(a, x) for(auto &a: x)
#define _ << " " <<
#define INF 1E9
#define INF64 1E18

using namespace std;

template<class T1, class T2> void pr(const pair<T1,T2>& x);
template<class T, size_t SZ> void pr(const array<T,SZ>& x);
template<class T> void pr(const vector<T>& x);
template<class T> void pr(const set<T>& x);
template<class T1, class T2> void pr(const map<T1,T2>& x);
template<class T> void pr(const T& x) { cout << x; }
template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
  pr(first); pr(rest...);
}
template<class T1, class T2> void pr(const pair<T1,T2>& x) {
  pr("{",x.first,", ",x.second,"}");
}
template<class T> void prContain(const T& x) {
  pr("{");bool fst = 1; TRAV(a,x) pr(!fst?", ":"",a), fst = 0;pr("}");
}
template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
template<class T> void pr(const vector<T>& x) { prContain(x); }
template<class T> void pr(const set<T>& x) { prContain(x); }
template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }

void ps() { pr("\n"); }
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
  pr(first," "); ps(rest...); // print w/ spaces
}

template<typename T> int remin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<typename T> int remax(T& a,const T& b){if(b>a){a=b;return true;}return false;}

typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

template<class T, int S>
struct Fenwick_Tree {
  vector<int> bit = vi(S+1);
  inline int low_bit(int idx) { return idx&(-idx); }
  T sum(int idx) {
    T total = 0;
    int k = idx + 1;
    while (k > 0) {
      total += bit[k];
      k -= low_bit(k);
    }
    return total;
  }
  void update(int idx, int v) {
    int k = idx + 1;
    while (k < S+1) {
      bit[k] += v;
      k += low_bit(k);
    }
  }
  T query(int l, int r) {
    return sum(r) - sum(l-1);
  }
};

int main(int argc, const char **argv) {
  Fenwick_Tree<ll, 10> ft;
  vi v = {4, 5, 6, 47, 41, 5, 65, 615, 1, 586};
  int N = SZ(v);
  for (int i = 0; i < N; ++i) {
    ft.update(i, v[i]);
  }
  for (int l = 0; l < N; ++l) {
    for (int r = l; r < N; ++r) {
      int sum = 0;
      for (int k = l; k <= r; ++k) {
        sum += v[k];
      }
      assert(sum == ft.query(l, r));
    }
  }

  return 0;
}
