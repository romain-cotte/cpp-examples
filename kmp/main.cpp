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

#include "util/assert.hpp"
#include "util/vector.hpp"

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


// Given a text txt[0..n-1] and a pattern pat[0..m-1], write a function
// search(char pat[], char txt[]) that prints all occurrences of pat[] in txt[].
// You may assume that n > m.

// lps[i] = the longest proper prefix of pat[0..i] which is also a suffix of
// pat[0..i].

// how to know how many characters to be skipped. To know this,
// we pre-process pattern and prepare an integer array
// lps[] that tells us the count of characters to be skipped.

// For the pattern "AABAACAABAA",
// lps[] is [0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5]
// longest proper prefix which is also suffix

vi lps_naive(const char *pat) {
  int S = strlen(pat);
  vi lps(S);
  lps[0] = 0;
  for (int i = 1; i < S; ++i) {
    for (int j = 1; j <= i; ++j) {
      bool ok = true;
      for (int k = 0; k < j; ++k) {
        // ps(k, i-j+k+1);
        if (pat[k] != pat[i-j+k+1]) {
          ok = false;
          break;
        }
      }
      if (ok) lps[i] = j;
    }
  }
  return lps;
}

vi lps_opt(const char *pat) {
  int S = strlen(pat);
  vi lps(S);
  int i = 1, len = 0;
  while (i < S) {
    if (pat[i] == pat[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[len-1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }
  return lps;
}


template<typename T>
vector<int> lps(const T &a) {
  int n = a.size();
  vector<int> pi(n);
  int j = 0;
  for (int i = 1; i < n; i++) {
    while (j > 0 && a[i] != a[j]) j = pi[j - 1];
    j += ((a[i] == a[j]) ? 1 : 0);
    pi[i] = j;
  }
  return pi;
}

int SP, ST;

// TODO add research!!


int search(const char *pat, const char *txt) {
  int SP = strlen(pat);
  int ST = strlen(txt);
  vi lps = lps_opt(pat);
  int matches = 0, i = 0, j = 0;
  while (i < ST) {
    if (txt[i] == pat[j]) {
      ++j;
      ++i;
    }
    if (j == SP) {
      matches++;
      j = lps[j-1];
    } else if (i < ST && txt[i] != pat[j]) {
      if (j != 0) {
        j = lps[j-1];
      } else {
        i = i + 1;
      }
    }
  }
  return matches;
}

int main(int argc, const char **argv) {
  const char *p0 = "AAACAAAA";
  assert_equals(lps_naive(p0), lps_opt(p0));
  const char *p1 = "ABCABCD";
  assert_equals(lps_naive(p1), lps_opt(p1));
  const char *p2 = "AABAACAABAA";
  assert_equals(lps_naive(p2), lps_opt(p2)); // [0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5]
  string str(p2);
  cout << "::" << lps(str) << endl;

  const char *pat = "AACA";
  const char *txt = "AACBAACAACA";
  printf("%d\n", search(pat, txt));

  return 0;
}
