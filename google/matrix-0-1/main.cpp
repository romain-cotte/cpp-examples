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

#define INF 1E9
#define INF64 2E18

using namespace std;

template<class T1, class T2> void pr(const pair<T1,T2>& x);
template<class T, size_t SZ> void pr(const array<T,SZ>& x);
template<class T> void pr(const vector<T>& x);
template<class T, class C> void pr(const set<T,C>& x);
template<class T, class C> void pr(const multiset<T,C>& x);
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

template<class T>
struct RMQ {
  vector<vector<T>> stor;
  vi arr;
  int sz;
  RMQ(const vi &_arr) {
    sz = _arr.size();
    stor.assign(sz, vector<T>(32-__builtin_clz(sz)));
    arr = _arr;
    for (int i = 0; i < (int)arr.size(); ++i) stor[i][0] = i;
    for (int j = 1; j < 32 - __builtin_clz(sz); ++j) {
      for (int i = 0; i < sz-(1<<(j-1)); ++i) {
        stor[i][j] = comb(stor[i][j-1], stor[i+(1<<(j-1))][j-1]);
      }
    }
  }
  // WARNING: MINIMUM!!
  int comb(int a, int b) const {
    if (arr[a] < arr[b]) return a;
    return b;
  }

  T query(int l, int r) const {
    int x = 31-__builtin_clz(r-l+1);
    return comb(stor[l][x], stor[r-(1<<x)+1][x]);
  }
};

int max_area(const RMQ<int> &rmq, int l, int r) {
  if (r < l) return 0;
  int i = rmq.query(l, r);
  int ans = (r-l+1) * rmq.arr[i];
  remax(ans, max_area(rmq,   l, i-1));
  remax(ans, max_area(rmq, i+1,   r));
  return ans;
}

int R, C;

int sol1(const vector<vi> &mat) {
  vector<vi> pref(R+1, vi(C+1));
  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      pref[r+1][c+1] = pref[r][c+1] + pref[r+1][c] - pref[r][c];
      pref[r+1][c+1] += mat[r][c] == 1;
    }
  }

  auto get = [&pref](int r1, int c1, int r2, int c2) {
    return pref[r2+1][c2+1] - pref[r2+1][c1] - pref[r1][c2+1] + pref[r1][c1];
  };

  int ans = 0;
  vi vans;
  for (int r1 = 0; r1 < R; ++r1) {
    for (int c1 = 0; c1 < C; ++c1) {
      for (int r2 = r1; r2 < R; ++r2) {
        for (int c2 = c1; c2 < C; ++c2) {
          int r = get(r1, c1, r2, c2);
          if (r == (r2-r1+1) * (c2-c1+1)) {
            if (remax(ans, get(r1, c1, r2, c2))) {
              vans = {r1, c1, r2, c2};
            }
          }
        }
      }
    }
  }
  return ans;
  // ps(ans, vans);
}


int sol2(const vector<vi> &mat) {
  vector<vi> dp(R+1, vi(C));
  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      dp[r+1][c] = mat[r][c] == 0 ? 0: dp[r][c] + 1;
    }
  }
  int ans = 0;
  for (vi row: dp) {
    RMQ<int> rmq(row);
    remax(ans, max_area(rmq, 0, C-1));
  }
  return ans;
}

inline int max_area(const vi &v) {
  int ans = 0;
  int n = v.size();
  vi st;
  for (int i = 0; i < n; ++i) {
    while (!st.empty() && v[i] < v[st.back()]) {
      int t = st.back();
      st.pop_back();
      remax(ans, v[t] * (st.empty() ? i: i - st.back() - 1));
      ps(v[t], st.empty() ? i: i - st.back() - 1);
    }
    st.push_back(i);
  }
  ps("--");
  while (!st.empty()) {
    int t = st.back();
    st.pop_back();
    remax(ans, v[t] * (st.empty() ? n: n - st.back() - 1));
    ps(v[t], st.empty() ? n: n - st.back() - 1);
  }
  return ans;
}

int sol3(const vector<vi> &mat) {
  vector<vi> dp(R+1, vi(C));
  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      dp[r+1][c] = mat[r][c] == 0 ? 0: dp[r][c] + 1;
    }
  }

  int ans = 0;
  for (int r = 0; r <= R; ++r) {
    remax(ans, max_area(dp[r]));
  }
  return ans;
}

int main(int argc, const char **argv) {
  R = 10, C = 10;
  // vector<vi> mat(R, vi(C));
  // random_device rd;
  // mt19937
  // gen(chrono::steady_clock::now().time_since_epoch().count());
  // uniform_int_distribution<>dist(0, 5);
  // clock_t t_clock;

  // float total2 = 0, total3 = 0;
  // for (int tt = 0; tt < 1000; ++tt) {
  //   for (int r = 0; r < R; ++r) {
  //     for (int c = 0; c < C; ++c) {
  //       mat[r][c] = dist(gen) < 1 ? 0: 1;
  //     }
  //   }
  //   ps("matrix:");
  //   for (vi row: mat) {
  //     ps(row);
  //   }
  //   t_clock = clock();
  //   int ans2 = sol2(mat);
  //   total2 += ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000;
  //   t_clock = clock();
  //   int ans3 = sol3(mat);
  //   total3 += ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000;
  //   assert(ans2 == ans3);
  //   assert(sol1(mat) == ans2);
  //   ps(ans2, ans3);
  // }
  // ps(total2, total3);

  ps(max_area({10, 4, 3, 100, 80, 50, 2}));


  return 0;
}
