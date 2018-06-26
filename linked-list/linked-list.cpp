#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <time.h>
#include <unordered_set>
#include <vector>

using namespace std;

namespace linked_list {

class Integer {

public:
  Integer(int k) {
    while (k) {
      digits.push_back(k%10);
      k = k/10;
    }
  }
  void print() const {
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
      cout << *it;
    }
    cout << endl;
  }

  friend Integer operator+(Integer lhs, const Integer &rhs) {
    Integer res(lhs);
    unsigned int r = 0;

    for (int i = 0; i < digits.size(); ++i) {
      res.digits[i] += digits[i] + r;
      r = res.digits[i] - res.digits[i] % 10;
      res.digits[i] %= 10;
    }

    for (auto it = digits.begin(); it != digits.end(); ++it) {

      cout << *it;
    }
    return res;
  }

private:
  vector<int> digits;
};

}

int main(int argc, const char **argv) {
  std::cout << "0:" << 0 << std::endl;
  linked_list::Integer a(1567);
  linked_list::Integer b(19);
  b.print();
  linked_list::Integer c = a + b;
  c.print();
  return 0;
}
