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

struct Trie {
  struct Node {
    vector<Node*> nxt = vector<Node*>(26);
    int cnt = 0;
  };
  Node *head = new Node();
  void insert(string s) {
    return insert(head, s, 0);
  }
  void insert(Node *cur, const string &s, int i) {
    cur->cnt++;
    if (i == (int)s.size()) {
      return;
    }
    char c = s[i] - 'a';
    if (!cur->nxt[c]) cur->nxt[c] = new Node();
    insert(cur->nxt[c], s, i+1);
  }
  int count(string s) {
    return count(head, s, 0);
  }
  int count(Node *cur, const string &s, int i) {
    if (i == (int)s.size()) {
      return cur->cnt;
    }
    char c = s[i]-'a';
    if (!cur->nxt[c]) return 0;
    return count(cur->nxt[c], s, i+1);
  }
} trie;


void solve() {
  string op, s;
  int n; cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> op >> s;
    if (op == "add") {
      trie.insert(s);
    } else {
      int c = trie.count(s);
      printf("%d\n", c);
    }
  }
}

int main(int argc, const char **argv) {
  solve();
  return 0;
}
