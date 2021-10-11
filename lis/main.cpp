/**
 * Longuest Increasing Sequence with backtracking
 */
#include "util/assert.hpp"
#include "util/vector.hpp"

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
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>

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


vi seq;

int lis(const vector<int> & a) {
  int n = a.size();
  vector<int> d(n+1, INF), pr(n+1, -1);
  vi ind(n+1, -1);
  d[0] = -INF;
  for (int i = 0; i < n; i++) {
    // change for upper_bound for not strictly
    int j = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
    if (d[j-1] <= a[i] && a[i] <= d[j]) {
      d[j] = a[i];
      ind[j] = i;
      pr[i] = ind[j-1];
    }
  }
  int ans = 0;
  for (int i = 0; i <= n; i++) {
    if (d[i] < INF) {
      ans = i;
    }
  }
  seq.clear();
  seq = {};
  int idx = ind[ans];
  while (idx != -1) {
    seq.push_back(idx);
    idx = pr[idx];
  }
  reverse(seq.begin(), seq.end());
  ps(seq);
  return ans;
}

vector<int> lis_seq(const vector<int> &a) {
  // declare the set with a custom comparison function
  // that compares values instead of indices
  auto compare = [&](int x, int y) {
    return a[x] < a[y];
  };
  set<int, decltype(compare)> S(compare);

  // process the a; for each length
  // maintain the index of the best end so far
  vector<int> previous(a.size(), -1);
  for (int i = 0; i < (int)a.size(); ++i) {
    auto it = S.insert(i).first;
    if (it != S.begin()) {
      previous[i] = *prev(it);
    }
    if (*it == i && next(it) != S.end()) {
      S.erase(next(it));
    }
  }
  // reconstruct the indices that form
  // one possible optimal answer
  vector<int> ind, ans;
  ind.push_back(*S.rbegin());
  ans.push_back(a[*S.rbegin()]);
  while (previous[ind.back()] != -1) {
    int idx = previous[ind.back()];
    ind.push_back(idx);
    ans.push_back(a[idx]);
  }
  reverse(ind.begin(), ind.end());
  reverse(ans.begin(), ans.end());
  return ans;
}

int main(int argc, const char **argv) {
  // vi seq = {};
  // assert_equals(lis(seq), {});

  // seq = {1};
  // assert_equals(lis(seq), {1});

  // seq = {1, 1};
  // assert_equals(lis(seq), {1});

  // seq = {7, 15, 6, 4, 4, 10, 13 };
  // assert_equals(lis_seq(seq), {4, 10, 13});
  printf("%d\n", lis({10, 7, 3, 9, 20, 12, 6, 8, 15}));

  return 0;
}
