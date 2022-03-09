#ifndef UTIL_ASSERT_H
#define UTIL_ASSERT_H

#include <vector>

void print_ok();
void assert_equals(std::vector<int> v1, std::vector<int> v2);
void assert_equals(int a, int b);
template<class T> extern void assert_equals(T *a, T *b);

#endif /* UtilAssert_H */
