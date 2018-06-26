#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <limits>
#include <sstream>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <map>
#include <assert.h>

using namespace std;

typedef vector<int> vi;
typedef vector<string> vs;
typedef long long ll;
typedef long long int lli;
typedef pair<int, int> pii;


template <typename T>
class Min_heap {
public:
  Min_heap() {

  };
  Min_heap(vector <T> v) {
    for (auto el: v) {
      push(el);
    }
  };

  template<typename U>
  friend std::ostream& operator<<(std::ostream&, const Min_heap<U>&);

  bool empty() {
    return _arr.empty();
  }

  T pop() {
    if (_arr.empty()) {
      throw "Empty";
    }
    T first = _arr.front();
    if (_arr.size() == 1) {
      _arr.pop_back();
      return first;
    }
    T back = _arr.back();
    _arr.pop_back();
    _arr[0] = back;
    percolate_down(0);
    return first;
  };

  void push(T el) {
    _arr.push_back(el);
    bubble_up(_arr.size()-1);
  }

private:
  void percolate_down(int idx) {
    int l = (idx + 1) << 1 - 1;
    int r = l + 1;
    if (l >= _arr.size()) {
      return;
    }
    if (_arr[idx] > _arr[l]) {
      swap(_arr[idx], _arr[l]);
      return;
    }
    if (r < _arr.size()) {
      if (_arr[idx] > _arr[r]) {
        swap(_arr[idx], _arr[r]);
        return;
      }
    }
  }

  void bubble_up(int idx) {
    if (idx == 0) return;
    int p = ((idx + 1) >> 1) - 1;
    if (_arr[idx] < _arr[p]) {
      swap(_arr[idx], _arr[p]);
      return bubble_up(p);
    }
  }

  vector<T> _arr;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Min_heap<T>& h) {
  for (auto el: h._arr) {
    out << el << " ";
  }
  return out;
}

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

int main(int argc, const char **argv) {
  clock_t time = clock();
  vector<int> v = {6, 7, 3, 10, 11, 4, 2, 1, 3 };
  vector<int> r;
  Min_heap<int> h(v);

  while(!h.empty()) {
    r.push_back(h.pop());
  }

  sort(v.begin(), v.end());
  cout << v << endl;
  cout << r << endl;

  time = clock() - time;
  printf("Time %d clocks, %.3f milliseconds.\n",
         (int)time,
         ((float)time)/CLOCKS_PER_SEC * 1000);
  return 0;
}
