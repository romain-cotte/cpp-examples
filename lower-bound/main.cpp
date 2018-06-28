
#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

template <class T>
std::ostream& operator<< (std::ostream& out, const vector<T>& v) {
  out << "[";
  size_t last = v.size() - 1;
  for(size_t i = 0; i < v.size(); ++i) {
    out << v[i];
    if (i != last) {
      out << ", ";
    }
  }
  out << "]";
  return out;
}

int lower_bound_1(vi::iterator begin, vi::iterator end, int el) {
  if (begin != end && el < *begin) return 0;
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

void test_lower_bound(vi v, int el, function<int (vi::iterator, vi::iterator, int)> func) {
  int lower = func(v.begin(), v.end(), el);
  assert(lower == lower_bound(v.begin(), v.end(), el) - v.begin());
  printf("lower_bound %d of ", el);
  cout << v;
  printf(" = %d OK\n", lower);
}

int main(int argc, const char **argv) {

  vi v = {};
  test_lower_bound(v, 3, lower_bound_1);

  v = { 1 };
  test_lower_bound(v, 3, lower_bound_1);

  v = { 5 };
  test_lower_bound(v, 3, lower_bound_1);

  v = { 1, 5, 5, 6, 10 };
  test_lower_bound(v, 3, lower_bound_1);
  test_lower_bound(v, 5, lower_bound_1);
  test_lower_bound(v, 15, lower_bound_1);

  return 0;
}
