#include "util/assert.hpp"
#include "util/vector.hpp"

void print_ok() {
  printf(" ... OK\n");
}

void assert_equals(std::vector<int> v1, std::vector<int> v2) {
  int s = v1.size();
  std::cout << v1 << " == " << v2;
  assert(s == (int)v2.size());
  for (int i = 0; i < s; ++i) {
    assert(v1[i] == v2[i]);
  }
  print_ok();
}

template<class T>
void assert_equals(T *arr1, T *arr2) {
  int N = sizeof(arr1) / sizeof(T);
  int M = sizeof(arr2) / sizeof(T);
  assert(N == M);
  for (int i = 0; i < N; ++i) {
    assert(arr1[i] == arr2[i]);
  }
  print_ok();
}

template void assert_equals<int>(int *a, int *b);

void assert_equals(int a, int b) {
  printf("%d == %d", a, b);
  assert(a == b);
  print_ok();
}
