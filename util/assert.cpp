#include "util/assert.hpp"
#include "util/vector.hpp"

void assert_equals(std::vector<int> v1, std::vector<int> v2) {
  int s = v1.size();
  std::cout << v1 << " == " << v2;
  assert(s == (int)v2.size());
  for (int i = 0; i < s; ++i) {
    assert(v1[i] == v2[i]);
  }
  std::cout << " ... OK" << std::endl;
}
