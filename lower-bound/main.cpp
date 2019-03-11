#include "util/assert.hpp"
#include "util/vector.hpp"

#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

int lower_bound_vi(vi::iterator begin, vi::iterator end, int el) {
  if (begin != end && el <= *begin) return 0;
  vi::iterator _begin = begin, mid;
  while (end - begin > 1) {
    mid = begin + (end - begin)/2;
    if (el <= *mid) {
      end = mid;
    } else {
      begin = mid;
    }
  }
  return end - _begin;
}

template<class BidirIt, class T>
int lower_bound_generic(BidirIt begin, BidirIt end, T el) {
  if (begin != end && el <= *begin) return 0;
  BidirIt _begin = begin, mid;
  while (end - begin > 1) {
    mid = begin + (end - begin)/2;
    if (el <= *mid) {
      end = mid;
    } else {
      begin = mid;
    }
  }
  return end - _begin;
}

template<class T>
void test_lower_bound(vector<T> v, T el, function<int (vi::iterator, vi::iterator, int)> func) {
  int lower = func(v.begin(), v.end(), el);
  assert(lower == lower_bound(v.begin(), v.end(), el) - v.begin());
  printf("lower_bound %d of ", el);
  cout << v;
  printf(" = %d OK\n", lower);
}

int main(int argc, const char **argv) {

  vi v = {};
  test_lower_bound(v, 3, lower_bound_vi);
  assert_equals(lower_bound_generic(v.begin(), v.end(), 3), 0);

  v = { 1 };
  test_lower_bound(v, 3, lower_bound_vi);
  assert_equals(lower_bound_generic(v.begin(), v.end(), 3), 1);

  v = { 5 };
  test_lower_bound(v, 3, lower_bound_vi);
  assert_equals(lower_bound_generic(v.begin(), v.end(), 3), 0);

  v = { 1, 5, 5, 6, 10 };
  test_lower_bound(v, 3, lower_bound_vi);
  assert_equals(lower_bound_generic(v.begin(), v.end(), 3), 1);
  test_lower_bound(v, 5, lower_bound_vi);
  assert_equals(lower_bound_generic(v.begin(), v.end(), 5), 1);

  test_lower_bound(v, 15, lower_bound_vi);
  assert_equals(lower_bound_generic(v.begin(), v.end(), 15), 5);

  test_lower_bound(v, 1, lower_bound_vi);
  assert_equals(lower_bound_generic(v.begin(), v.end(), 1), 0);
  assert_equals(lower_bound_generic(v.begin(), v.end(), 1), 0);

  int arr[] = {4, 5, 6};
  assert_equals(lower_bound_generic(arr, arr + 2, 5), 1);

  v = {6, 5, 4};
  assert(lower_bound_generic(v.rbegin(), v.rend(), 6) == 2);


  // STL

  v = { 1, 6, 8 };
  printf("%d", lower_bound(v.begin(), v.end(), 8) - v.begin());


  return 0;
}
