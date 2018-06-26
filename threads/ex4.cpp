/**
 * Race conditions
 * Please see https://www.classes.cs.uchicago.edu/archive/2013/spring/12300-1/labs/lab6/
 *
 * for i in {1..10000}; do ./ex4; done | sort | uniq -c
 * returns
 * 10000 accum = 2870
 */
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

atomic<int> accum(0);

int accum = 0;
mutex accum_mutex;

void square(int x) {
  int temp = x * x;
  accum_mutex.lock();
  accum += temp;
  accum_mutex.unlock();
}

void square2(int x) {
  accum += x * x;
}

int main() {
  vector<thread> ths;
  for (int i = 1; i <= 20; i++) {
    ths.push_back(thread(&square, i));
  }

  for (auto& th : ths) {
    th.join();
  }
  cout << "accum = " << accum << endl;

  return 0;
}
