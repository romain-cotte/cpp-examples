/**
 * Longuest Increasing Sequence with backtracking
 */
#include "util/assert.hpp"
#include "util/vector.hpp"

#include <bits/stdc++.h>

#define SZ(x) (int)(x.size())
#define F0(i,n) for(int i=0;i<n;i++)
#define F1(i,n) for(int i=1;i<=n;i++)
#define FI(i,n) for(int i=0;i<=n;i++)
#define TR(x) cout << #x << " = " << x << endl
#define _ << " " <<
#define INF 1E9

using namespace std;
typedef vector<int> vi;

vi seq;

template<class BidirIt, class T>
int lower_bound_generic(BidirIt begin, BidirIt end, const T el) {
  if (begin != end && el <= seq[*begin]) return 0;
  BidirIt _begin = begin, mid;
  while (end - begin > 1) {
    mid = begin + (end - begin)/2;
    if (el <= seq[*mid]) {
      end = mid;
    } else {
      begin = mid;
    }
  }
  return end - _begin;
}

vi lis(const vi &seq) {
  const int SIZE = SZ(seq);
  vi tailIndexes, previous, ret;
  previous.resize(SIZE);
  int len = 0, idx;
  F0(i, SIZE) {
    previous[i] = -1;
    if (!len) {
      tailIndexes.push_back(i);
      len++;
    } else {
    idx = lower_bound_generic(tailIndexes.begin(), tailIndexes.end(), seq[i]);
      if (idx == len) {
        previous[i] = tailIndexes[len-1];
        tailIndexes.push_back(i);
        len++;
      } else {
        previous[i] = tailIndexes[len-1];
        tailIndexes[idx] = i;
      }
    }
  }

  for (int i = len-1; i != -1; i = previous[i]) {
    ret.push_back(seq[tailIndexes[i]]);
  }
  reverse(ret.begin(), ret.end());
  return ret;
}


int main(int argc, const char **argv) {

  seq = {};
  assert_equals(lis(seq), {});

  seq = {1};
  assert_equals(lis(seq), {1});

  seq = {1, 1};
  assert_equals(lis(seq), {1});

  seq = {7, 15, 6, 4, 4, 10, 13 };
  assert_equals(lis(seq), {4, 10, 13});

  return 0;
}
