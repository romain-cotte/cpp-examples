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
#define _ << " " <<
#define INF 1E9

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)
#define sz(x) (int)x.size()
#define beg(x) x.begin()
#define en(x) x.end()
#define all(x) beg(x), en(x)
#define resz resize

using namespace std;
typedef vector<int> vi;

template<typename T> int remin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<typename T> int remax(T& a,const T& b){if(b>a){a=b;return true;}return false;}


template<class T, int S>
struct RMQ {
  // has to be declared as global variable!
  T stor[S][32-__builtin_clz(S)];
  vi x;

  int comb(int a, int b) {
    if (x[a] > x[b]) return a;
    return b;
  }

  void build(vi _x) {
    x = _x;
    F0(i, SZ(x)) stor[i][0] = i;
    for (int j = 1; j < 32-__builtin_clz(S); ++j) {
      F0(i, S-(1<<(j-1))) {
        stor[i][j] = comb(stor[i][j-1], stor[i+(1<<(j-1))][j-1]);
      }
    }
  }

  T query(int l, int r) {
    int x = 31-__builtin_clz(r-l+1);
    return comb(stor[l][x], stor[r-(1<<x)+1][x]);
  }
};

RMQ<int, 1005> rmq;

int main(int argc, const char **argv) {
  //        0                   5                 9  10
  vi v = { 15, 34, 58, 3, 90, 133, 149, 43, 58, 289, 67 };
  rmq.build(v);

  assert(rmq.query(0, 10) == 9);
  assert(rmq.query(5, 7) == 6);
  assert(rmq.query(1, 9) == 9);
  assert(rmq.query(0, 3) == 2);
  assert(rmq.query(0, 0) == 0);
  assert(rmq.query(1, 1) == 1);
  assert(rmq.query(2, 2) == 2);
  assert(rmq.query(3, 3) == 3);

  // printf("%d\n", rmq.query(0, 10));
  // printf("%d\n", rmq.query(5, 7));
  // printf("%d\n", rmq.query(1, 9));
  // printf("%d\n", rmq.query(0, 3));
  // printf("%d\n", rmq.query(0, 0));
  // printf("%d\n", rmq.query(1, 1));
  // printf("%d\n", rmq.query(2, 2));
  // printf("%d\n", rmq.query(3, 3));


  return 0;
}
