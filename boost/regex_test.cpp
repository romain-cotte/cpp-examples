#include <boost/regex.hpp>

int main() {
  boost::regex re;
  std::string str;
  boost::smatch match;
  boost::regex_match(str, match, re);

  return 0;
}

// Only version 5 it works!

// g++ -O1 -o regex_test.o regex_test.cpp -lboost_regex
// g++ -std=c++17 -O1 -o regex_test.o regex_test.cpp -lboost_regex

// Or with clang -O0:

// clang++-3.8 -O0 -o regex_test.o0 regex_test.cpp -lboost_regex

// But not with clang -O1:

// clang++-3.8 -O1 -o regex_test.o1 regex_test.cpp -lboost_regex

// Pour corriger l'erreur fatal error: 'cstddef' file not found j'ai installé g++-7


// sudo apt install libboost-all-dev
