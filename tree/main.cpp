/**
 * Implement an algorithm to determine if a string has all unique characters.
 * What if you cannot use additional data structure?
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
typedef vector<string> vs;
typedef long long ll;
typedef long long int lli;
typedef pair<int, int> pii;



bool areAllUnique(string str) {
  unordered_set<char> s;
  for (unsigned int i = 0; i < str.size(); i++) {
    if (s.find(str[i]) != s.end()) return false;
    s.insert(str[i]);
  }
  return true;
}


void sortInsertChar(string &str, int n) {
  char e = str[n];
  char d;
  for (int i = 0; i < n; i++) {
    if (str[i] > e) {
      d = str[i];
      str[i] = e;
      for (int j = i+1; j <= n; j++) {
        e = str[j];
        str[j] = d;
        d = e;
      }
      return;
    }
  }
}

void sortInsert(string& str) {
  for (unsigned int i = 1; i < str.size(); i++) {
    sortInsertChar(str, i);
  }
}

bool areAllUnique2(string& str) {
  if (str.size() <= 1) return true;
  sortInsert(str);
  for (unsigned int i = 0; i < str.size() - 1; i++) {
    if (str[i] == str[i+1]) return false;
  }
  return true;
}

int main(int argc, const char **argv) {
  string str = "acazergkpjzhpkjrhtezmlkrjtmlzekjrmlkdb";
  cout << areAllUnique(str) << endl;
  cout << areAllUnique2(str) << endl;
  return 0;
}
