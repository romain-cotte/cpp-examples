/**
 * Race conditions
 * Please see https://www.classes.cs.uchicago.edu/archive/2013/spring/12300-1/labs/lab6/
 *
 */
#include <iostream>
#include <future>
#include <chrono>
#include <thread>

using namespace std;

int main() {
  packaged_task<int()> task([](){ return 7; }); // wrap the function
  future<int> f1 = task.get_future();  // get a future
  thread(move(task)).detach(); // launch on a thread

  // future from an async()
  future<int> f2 = async(launch::async, [](){ return 8; });

  // future from a promise
  promise<int> p;
  future<int> f3 = p.get_future();
  thread(
    [](promise<int> p){ p.set_value_at_thread_exit(9); },
    move(p)
  ).detach();

  cout << "Waiting..." << flush;
  f1.wait();
  f2.wait();
  f3.wait();
  cout << "Done!" << endl << "Results are: ";
  cout << f1.get() << ' ' << f2.get() << ' ' << f3.get() << endl;
  return 0;
}
