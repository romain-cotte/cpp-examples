#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
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

stack<ii> s1, s2;

void ins(int v) {
  if (s1.empty()) s1.push(ii(v, v));
  else s1.push(ii(v, min(v, s1.top().second)));
}

void del() {
  if (s2.empty()) {
    // transfer elements from s1 to s2;
    while (!s1.empty()) {
      ii p = s1.top();
      s1.pop();
      s2.push(ii(p.first, s2.empty() ? p.first: min(s2.top().second, p.first)));
    }
  }
  s2.pop();
}

/**
 * We suppose at least one element exists
 */
int get_min() {
  if (s1.empty() || s2.empty()) {
    return s1.empty() ? s2.top().second: s1.top().second;
  }
  return min(s1.top().second, s2.top().second);
}


int main(int argc, const char **argv) {
  vi v = { 5, 10, 7, 15, 3, 4, 23, 17, 10, 2 };
  vi mn;
  int N = SZ(v);
  mn.resize(N);
  int b = 3;
  for (int i = 0; i < N; ++i) {
    ins(v[i]);
    if (i >= b) del();
    mn[i] = get_min();
    printf("%d %d\n", i, get_min());
  }
  ps(v);
  ps(mn);

  return 0;
}
