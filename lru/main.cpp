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
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <unordered_map>
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



class LRU
{
public:
  LRU() {
  };

  void set(string key, string value) {
    if (map.find(key) != map.end() || map.size() < this->max_size) {
      last_used.remove(key);
      last_used.push_front(key);
      map[key] = value;
    } else {
      string last = last_used.back();
      last_used.pop_back();
      map.erase(last);
      last_used.push_front(key);
      map[key] = value;
    }
    this->display();
  }

  void display() {
    for (string s: this->last_used) {
      printf("%s ", s.c_str());
    }
    printf("\n");
    for (pair<string, string> p: map) {
      string k = p.first;
      string v = p.second;
      printf("%s %s, ", k.c_str(), v.c_str());
    }
    printf("\n");
  }


private:
  unordered_map<string, string> map;
  list<string> last_used;
  int max_size = 3;
};


int main(int argc, const char **argv) {
  LRU *lru = new LRU();
  lru->set("a", "1");
  lru->set("b", "2");
  lru->set("c", "3");
  lru->set("d", "4");
  lru->set("a", "5");
  lru->set("d", "6");

  return 0;
}
