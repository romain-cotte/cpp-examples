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


struct IntervalTree {
  int center = INF;
  vii start, end;

  IntervalTree *left = NULL, *right = NULL;
  void print() {
    printf("center: %d\n", center);
    for (ii p: start) printf("%d %d, ", p.first, p.second);
    printf("\n");
    printf("left:\n");
    if (left != NULL) left->print();
    printf("right:\n");
    if (right != NULL) right->print();
  }

  void insert(ii seg) {
    int c = (seg.first+seg.second)/2;
    if (center == INF) {
      center = c;
    }
    if (seg.second < center) {
      if (left == NULL) left = new IntervalTree();
      left->insert(seg);
    } else if (center < seg.first) {
      if (!right) right = new IntervalTree();
      right->insert(seg);
    } else {
      start.push_back(seg);
      end.push_back(ii(seg.second, seg.first));
    }
  }

  vector<ii> intersect(int k) {
    vector<ii> response;
    if (k <= center) {
      auto lst = lower_bound(start.begin(), start.end(), ii(k+1, -INF));
      for (auto itr = start.begin(); itr != lst; ++itr) {
        response.push_back(*itr);
      }
      if (left != NULL) {
        auto aux = left->intersect(k);
        response.insert(response.end(), aux.begin(), aux.end());
      }
    } else {
      auto fst = lower_bound(end.begin(), end.end(), ii(k, -INF));
      for (auto itr = fst; itr != end.end(); ++itr) {
        response.push_back(*itr);
      }
      if (right != NULL) {
        auto aux = right->intersect(k);
        response.insert(response.end(), aux.begin(), aux.end());
      }
    }
    return response;
  }
};


int main(int argc, const char **argv) {
  vector<ii> segs = {
    {5, 6},
    {10, 18},
    {8, 13},
    {20, 29}
  };
  IntervalTree it;
  for (ii seg: segs) {
    it.insert(seg);
  }
  // ps(it.intersect(-1));
  // ps(it.intersect(6));
  // it.print();
  ps(it.intersect(20));

  return 0;
}
