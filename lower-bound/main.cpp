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

  // v = { 4, 5, 6 };
  // assert(lower_bound_generic(v.rbegin(), v.rend(), 6) == 2);

  v = { 5, 6 };
  printf("%d\n", lower_bound_generic(v.rbegin(), v.rend(), 6));
  test_lower_bound(v, 6, lower_bound_vi);

  // STL
  v = { 1, 6, 8 };
  printf("%d\n", lower_bound(v.begin(), v.end(), 8) - v.begin());
  assert(lower_bound(v.begin(), v.end(), 8) - v.begin() == 2);
  printf("%d\n", lower_bound(v.begin(), v.end(), 9) - v.begin());

  v = { 2, 3, 3, 7, 7, 8, 8 };
  // If the element does not exist, both lower_bound and upper_bound return
  // the index to the next element
  printf("%d\n", lower_bound(v.begin(), v.end(), 4) - v.begin());
  assert(lower_bound(v.begin(), v.end(), 4) - v.begin() == 3);
  printf("%d\n", upper_bound(v.begin(), v.end(), 4) - v.begin());
  assert(upper_bound(v.begin(), v.end(), 4) - v.begin() == 3);

  // If the element exists, upper_bound returns the next element from it
  printf("%d %d\n", upper_bound(v.begin(), v.end(), 7) - v.begin(), *upper_bound(v.begin(), v.end(), 7));

  return 0;
}
