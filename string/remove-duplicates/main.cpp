/**
 * Design an algorithm and write code to remove the duplicate characters in a
 * string without using any additional buffer. NOTE: One or two additional
 * variables are fine. An extra copy of the array is not.
 * FOLLOW UP
 * Write the test cases for this method.
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
#include <unordered_set>
#include <map>
#include <set>
#include <sstream>
#include <time.h>
#include <vector>

using namespace std;

void removeDuplicates(string &str) {
  unsigned int j;
  for (unsigned int i = 0; i < str.size(); i++) {
    j = i + 1;
    while (j < str.size()) {
      while (str[i] == str[j] && j < str.size()) {
        str.erase(j, 1);
      }
      j++;
    }
  }
}

int main(int argc, const char **argv) {
  string str = "acazergkpjzhpkjrhtezmlkrjtmlzekjrmlkdb";
  removeDuplicates(str);
  std::cout << "str:" << str << std::endl;
  str = "a";
  removeDuplicates(str);
  std::cout << "str:" << str << std::endl;
  return 0;
}
