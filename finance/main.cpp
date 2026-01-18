#include <algorithm>
#include <assert.h>
#include <bitset>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
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


// random_device rd{};
// mt19937 gen{rd()};

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());


vector<double> normal_dist(int n, double mu, double sigma) {
  normal_distribution<double> d{mu, sigma};
  vector<double> returns;
  returns.reserve(n);
  for (int i = 0; i < n; ++i) returns.push_back(d(gen));
  sort(returns.begin(), returns.end());
  return returns;
}

double mean(const vector<double> &v) {
  int n = v.size();
  double total = 0;
  for (int i = 0; i < n; ++i) {
    total += v[i];
  }
  return total / n;
};

double standard_deviation(const vector<double> &v) {
  int n = v.size();
  double M = mean(v);
  double variance = 0;
  for (int i = 0; i < n; ++i) {
    variance += (v[i]-M)*(v[i]-M);
  }
  variance /= n;
  return sqrt(variance);
};

double value_at_risk(const vector<double> &v, const double r = 0.05) {
  int n = v.size();
  int idx = static_cast<int> (r * n);
  return -v[idx];
};

void draw(const vector<double> &v, int boxes = 20) {
  map<int, unsigned> histogram{};
  int n = v.size();
  double mn = v[0], mx = v[n-1];
  double delta = (mx - mn) / boxes;
  for (int i = 0; i < n; ++i) {
    ++histogram[(int)((v[i]-mn) / delta)];
  }
  double star_cnt = n * 0.005;
  for (const auto [k, v] : histogram) {
    cout << setw(2) << k << ' ' << string(v / star_cnt, '*') << '\n';
  }
};



int main(int argc, const char **argv) {

  const int N = 10000;
  const double mu = 0.0005;
  const double sigma = 0.01;
  vector<double> returns = normal_dist(N, mu, sigma);


  const int n_sample = 10;
  for (int i = 0; i < n_sample; ++i) {
    ps(i, returns[i]);
  }
  for (int i = N-n_sample; i < N; ++i) {
    ps(i, returns[i]);
  }
  draw(returns);
  ps(mean(returns), standard_deviation(returns));
  ps("Value at risk  5%", value_at_risk(returns, 0.1));
  ps("Value at risk 10%", value_at_risk(returns, 0.05));


  return 0;
}
