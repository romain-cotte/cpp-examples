#include "util/assert.hpp"
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

void copy_vector(vi::iterator begin, vi::iterator end, vi &dest) {
  vi::iterator it = begin;
  while (it != end) {
    dest.push_back(*it);
    it++;
  }
}

template<class BidirIt>
void copy_vector_generic(BidirIt first, BidirIt last, vi &dest) {
  dest.clear();
  while (first != last) {
    dest.push_back(*first);
    first++;
  }
}

int main(int argc, const char **argv) {
  vi v = {1, 2, 3, 4};
  vi copy;

  copy_vector(v.begin(), v.end(), copy);
  assert_equals(v, copy);

  copy_vector_generic(v.begin(), v.end(), copy);
  assert_equals(v, copy);

  copy_vector_generic(v.rbegin(), v.rend(), copy);
  reverse(copy.begin(), copy.end());
  assert_equals(v, copy);

  int arr[] = {4, 5, 6};
  copy_vector_generic(arr, arr + 3, copy);
  vi expected_result = {4, 5, 6};
  assert_equals(copy, expected_result);

  copy_vector_generic(arr + 1, arr + 3, copy);
  expected_result = {5, 6};
  assert_equals(copy, expected_result);

  return 0;
}
