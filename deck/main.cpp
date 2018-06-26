/**
 * Deck of cards
 */
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
#include <vector>

using namespace std;
typedef vector<string> vs;
typedef long long ll;
typedef long long int lli;
typedef pair<int, int> pii;
#define SIZE 100

enum class Suit {
  Begin,
  HEARTS = Begin,
  CLUBS,
  SPADES,
  DIAMONDS,
  End
};

class Deck {
  vector<int> carts;
  public:
    Deck() {}
    void add(int i) {
      carts.push_back(i);
    }

    void add(Suit s) {
      int i = static_cast<int>(s);
      std::cout << "i:" << i << std::endl;
      carts.push_back(i);
    }

    void remove(int idx) {
      carts.erase(carts.begin() + idx);
    }

    void print() {
      for (auto it = carts.begin(); it != carts.end(); ++it) {
        cout << *it << endl;
      }
    }
};


int main(int argc, const char **argv) {
  Deck* d = new Deck();
  Deck* c = new Deck();
  d->add(Suit::CLUBS);
  // d->remove(0);
  d->add(15);
  d->print();
  c->add(100);
  c->print();
  return 0;
}
