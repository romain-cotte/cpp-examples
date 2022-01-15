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

random_device rd;
mt19937 gen(rd());

vi v = {10, 50, 100, 9, 0, 1};

struct RandomFreqPropValues {
  vi v, w; vector<ll> pre;
  ll sum = 0;
  RandomFreqPropValues(const vi &_v) : v(_v) {
    pre.resize(v.size());
    for (int i = 0; i < (int)v.size(); ++i) {
      pre[i] = (i? pre[i-1]:0) + v[i];
    }
    sum = pre.back();
  }
  RandomFreqPropValues(const vi &_v, const vi &_w) : v(_v), w(_w) {
    pre.resize(w.size());
    for (int i = 0; i < (int)w.size(); ++i) {
      pre[i] = (i? pre[i-1]:0) + w[i];
    }
    sum = pre.back();
  }
  int get() {
    uniform_int_distribution<ll>dist(0, sum);
    ll k = dist(gen);
    int idx = lower_bound(pre.begin(), pre.end(), k) - pre.begin();
    return v[idx];
  }
};

struct RandomInvFreqPropValues {
  vi v, w; vector<ll> pre;
  ll sum = 0;
  RandomInvFreqPropValues(const vi &_v) : v(_v) {
    int mx = *max_element(v.begin(), v.end());
    pre.resize(v.size());
    for (int i = 0; i < (int)v.size(); ++i) {
      pre[i] = (i? pre[i-1]:0) + max(1, (mx-v[i]));
    }
    sum = pre.back();
  }
  RandomInvFreqPropValues(const vi &_v, const vi &_w) : v(_v), w(_w) {
    int mx = *max_element(w.begin(), w.end());
    pre.resize(w.size());
    for (int i = 0; i < (int)w.size(); ++i) {
      pre[i] = (i? pre[i-1]:0) + max(1, (mx-w[i]));
    }
    sum = pre.back();
  }

  int get() {
    uniform_int_distribution<ll>dist(0, sum);
    ll k = dist(gen);
    int idx = lower_bound(pre.begin(), pre.end(), k) - pre.begin();
    return v[idx];
  }
};


int main(int argc, const char **argv) {

  clock_t t_clock = clock();


  RandomFreqPropValues random_freq(v);
  RandomInvFreqPropValues random_inv_freq(v);

  map<int, int> freq;
  for (int i = 0; i < 1000000; ++i) {
    freq[random_inv_freq.get()]++;
  }

  ps(freq);
  // code
  fprintf(
    stderr,
    "Time %.3f milliseconds.\n",
    ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000
  );
  return 0;
}
