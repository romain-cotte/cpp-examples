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
  Min_heap() {};
  Min_heap(vector <T> v) {
    for (auto el: v) {
      push(el);
    }
  };

  bool empty() {
    return _arr.empty();
  }

  T pop() {
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
    bubble_up(_arr.size() - 1);
  };

  template <typename U>
  friend ostream& operator<<(ostream& out, const Min_heap<U>& h);

private:
  void percolate_down(int idx) {
    const int S = _arr.size();
    int child;
    for (;((idx+1) << 1) - 1 <= S; idx = child) {
      child = ((idx+1) << 1) - 1;
      if (child != S && _arr[child + 1] < _arr[child]) {
        ++child;
      }
      if (_arr[idx] > _arr[child]) {
        swap(_arr[idx], _arr[child]);
      } else {
        break;
      }
    }
    return;
  }

  void bubble_up(int idx) {
    if (idx == 0) return;
    int p = (idx-1) >> 1;
    if (_arr[p] > _arr[idx]) {
      swap(_arr[p], _arr[idx]);
      bubble_up(p);
    }
  }

  vector<T> _arr;
};

template <typename T>
ostream& operator<<(ostream& out, const Min_heap<T>& h) {
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

  vector<int> v = {5, 6, 1, 10, 5, 6, 7849, 54, 654, 6854, 2};
  // vector<int> v = {6, 5, 7};
  vector<int> r;
  Min_heap<int>* h = new Min_heap<int>(v);

  cout << *h << endl;

  while (!h->empty()) {
    r.push_back(h->pop());
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
