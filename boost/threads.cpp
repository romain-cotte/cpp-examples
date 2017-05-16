#include <chrono>
#include <iostream>
#include <thread>

void foo() {
  std::cout << "foo" << std::endl;
}

void bar() {
  std::cout << "bar" << std::endl;
}

int main() {
  std::cout << std::thread::hardware_concurrency() << std::endl;


  std::thread first(&foo);     // spawn new thread that calls foo()
  std::thread second(bar);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}

