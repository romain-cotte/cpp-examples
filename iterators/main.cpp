#include <bits/stdc++.h>

#define SZ(x) (int)(x.size())
#define F0(i,n) for(int i=0;i<n;i++)
#define F1(i,n) for(int i=1;i<=n;i++)
#define FI(i,n) for(int i=0;i<=n;i++)
#define TR(x) cout << #x << " = " << x << endl
#define _ << " " <<
#define INF 1E9

using namespace std;
typedef vector<int> vi;

void copy_vector(vi::iterator begin, vi::iterator end, vi &dest) {
  vi::iterator it = begin;
  while (it != end) {
    dest.push_back(*it);
    it++;
  }
}

int main(int argc, const char **argv) {
  vi v = {1, 2, 3, 4};
  vi copy;

  copy_vector(v.begin(), v.end(), copy);

  cout << "Assertions...";
  assert(v.size() == copy.size());
  F0(i, SZ(v)) {
    assert(v[i] == copy[i]);
  }
  cout << "OK" << endl;

  return 0;
}
