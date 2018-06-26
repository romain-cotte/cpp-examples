/**
 * Please see https://www.classes.cs.uchicago.edu/archive/2013/spring/12300-1/labs/lab6/
 */
#include <iostream>
#include <thread>

using namespace std;

void func(int x) {
  cout << "Inside thread " << x << endl;
}

int main(int argc, const char **argv) {
  thread th(&func, 100);
  th.join();
  cout << "Outside thread" << endl;
  return 0;
}
