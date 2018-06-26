/**
 * Race conditions
 * Please see https://www.classes.cs.uchicago.edu/archive/2013/spring/12300-1/labs/lab6/
 *
 * for i in {1..10000}; do ./ex3; done | sort | uniq -c
 * returns
 * 1 accum = 2726
 * 1 accum = 2806
 * 1 accum = 2821
 * 1 accum = 2857
 * 9996 accum = 2870
 * beacause of inconsistency : reading the current value of accum and setting
 * the updated value is not an atomic (meaning indivisible) event
 */

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

int accum = 0;

void square(int x) {
  // Inconsistency:
  accum += x * x;
}
// mutex accum_mutex;

// void square2(int x) {
//   int temp = x * x;
//   accum_mutex.lock();
//   accum += temp;
//   accum_mutex.unlock();
// }

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
