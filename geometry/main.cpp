#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>


#define INF 2E9
#define INF64 4E18

using namespace std;

template<class T1, class T2> void pr(const pair<T1,T2>& x);
template<class T, size_t SZ> void pr(const array<T,SZ>& x);
template<class T> void pr(const vector<T>& x);
template<class T> void pr(const deque<T>& x);
template<class T, class C> void pr(const set<T,C>& x);
template<class T, class C> void pr(const multiset<T,C>& x);
template<class T1, class T2> void pr(const map<T1,T2>& x);
template<class... T> void pr(const tuple<T...>& tup);

const string COLOR_RESET = "\033[0m", GREEN = "\033[1;32m";
template<class T> void pr(const T& x) {
#if COLOR == true
  cout << GREEN << x << COLOR_RESET;
#else
  cout << x;
#endif
}

template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
  pr(first); pr(rest...);
}
template<class T1, class T2> void pr(const pair<T1,T2>& x) {
  pr("{",x.first,", ",x.second,"}");
}
template<class T> void prContain(const T& x) {
  pr("{");bool fst = 1; for(auto &a: x) pr(!fst?", ":"",a), fst = 0;pr("}");
}
template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
template<class T> void pr(const vector<T>& x) { prContain(x); }
template<class T> void pr(const deque<T>& x) { prContain(x); }
template<class T, class C> void pr(const set<T,C>& x) { prContain(x); }
template<class T, class C> void pr(const multiset<T,C>& x) { prContain(x); }
template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }

template<class T, size_t... I>
void pr(const T& tup, index_sequence<I...>) {
  pr("("); (..., (cout << (I == 0? "" : ", ") << get<I>(tup))); pr(")");
}
template<class... T>
void pr (const tuple<T...>& tup) {
  pr(tup, make_index_sequence<sizeof...(T)>());
}
void ps() { pr("\n"); }
void _ps_continue() { pr("\n"); }
template<class Arg, class... Args> void _ps_continue(const Arg& first, const Args&... rest) {
  pr(" ", first); _ps_continue(rest...);
}

#ifdef DEBUG_LOCAL
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
  pr(first); _ps_continue(rest...);
}
#else
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {}
#endif

template<typename T> int remin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<typename T> int remax(T& a,const T& b){if(a<b){a=b;return true;}return false;}

typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef double T;
typedef double data;

struct Point {
  T x, y;
  Point() {}
  Point(T _x, T _y) : x(_x), y(_y) { }
  void print() {
    printf("(%lf, %lf)", x, y);
  }
  bool operator==(const Point& p) const {
    return this->x == p.x && this->y == p.y;
  }
  Point operator+(const Point &p) const {
    return Point(this->x + p.x, this->y + p.y);
  }
  Point operator-(const Point &p) const {
    return Point(this->x - p.x, this->y - p.y);
  }
  Point operator*(const T v) const {
    return Point(this->x * v, this->y * v);
  }
  int cross_product(const Point &a, const Point &b) const {
    int x1 = a.x - this->x, x2 = b.x - this->x;
    int y1 = a.y - this->y, y2 = b.y - this->y;
    return x1*y2-y1*x2;
  }
};
ostream& operator<<(ostream& os, const Point& p) {
  os << "x: " << p.x << " y: " << p.y;
  return os;
}


T dot(const Point &p, const Point &q) {
  return p.x*q.x + p.y*q.y;
}

struct Line {
  // ax + by + c = 0;
  // slope of (b, -a)
  T a, b, c;
  Line(Point p, Point q) {
    a = q.y - p.y;
    b = p.x - q.x;
    c = q.x * p.y - p.x * q.y;
  }
  Line(T a, T b, T c) : a(a), b(b), c(c) {}
};

bool inline belong(Line l, Point p) {
  return abs(l.a * p.x + l.b * p.y + l.c) <= 1E-6;
}

inline T square(T a) {
  return a * a;
}

inline T distance_squared(Point p, Point q) {
  return square(p.x - q.x) + square(p.y - q.y);
}

inline T distance(Point p, Point q) {
  return sqrt(distance_squared(p, q));
}

struct Circle {
  Point c;
  T R;
  Circle() {}
  Circle(Point _c, T _R): c(_c), R(_R) {}
  bool inline is_inside(Point p) {
    return distance_squared(this->c, p) - this->R * this->R < 1E-9;
  }
};

// Point projection(Line l, Point p) {

// }

Line perpendicular(Line l, Point p) {
  Line ret{-l.b, l.a, l.b*p.x-l.a*p.y};
  return ret;
}


Point intersection(Line l1, Line l2) {
  T x, y;
  if (l1.a == 0) {
    y = -l1.c/l1.b;
    x = (l1.c*l2.b - l2.c*l1.b) / (l2.a * l1.b);
  } else {
    y = (l1.c*l2.a-l1.a*l2.c)/(l2.b-l1.b*l2.a);
    x = (-l1.c -l1.b * y) / l1.a;
  }
  return Point(x, y);
}


Point point_seg_coordinates(Point s, Point e, Point p) {
  T d = distance_squared(s, e);
  if (d == 0) return s;
  T t = max(0.0, min(1.0, dot(p-s, e-s) / d));
  return s + (e-s) * t;
}

T point_seg_distance(Point s, Point e, Point p) {
  return distance(point_seg_coordinates(s, e, p), p);
}


int main(int argc, const char **argv) {
#ifndef DEBUG_LOCAL
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#endif

  Point A(0, 0);
  Point B(1, 3);
  Point C(5, 0);


  Point M((A.x+C.x)/2, (A.y+C.y)/2);
  Point H(1, 0);

  Point O;
  Point K;

  Line AC = Line(A, C);
  Line BH = perpendicular(AC, B);
  Point h = intersection(AC, BH);


  cout << h << endl;

  return 0;
}
