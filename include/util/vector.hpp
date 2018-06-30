#ifndef UTIL_VECTOR_H
#define UTIL_VECTOR_H

#include <cstdio>
#include <iostream>
#include <vector>

// tempalte cannot be impleted in cpp files
template <class T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
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

#endif /* UtilVector_H */
