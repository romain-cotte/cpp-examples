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

void assert_equals(int a, int b) {
  printf("%d == %d", a, b);
  assert(a == b);
  print_ok();
}
