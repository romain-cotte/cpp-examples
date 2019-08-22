/**
 * Generate an input
 */
#include <iostream>
#include <random>

using namespace std;

#define SZ(x) (int)(x.size())
#define F0(i,n) for(int i=0;i<n;++i)
#define F1(i,n) for(int i=1;i<=n;++i)
#define TR(x) cout << #x << " = " << x << endl
#define _ << " _ " <<
#define NN 10005


#define MAX 1000000
int id[MAX], sz[MAX];

int root(int i) {
  while (i!=id[i]) {
    id[i] = id[id[i]];
    i = id[i];
  }
  return i;
}

bool find(int p, int q) {
  return root(p) == root(q);
}

bool unite(int p, int q) {
  int i = root(p);
  int j = root(q);
  if (j == i) return false;
  if (sz[i] < sz[j]) {
    id[j] = i;
    sz[i] += sz[j];
  } else {
    id[i] = j;
    sz[j] += sz[i];
  }
  return true;
}

int main(int argc, const char **argv) {
  random_device rd;
  mt19937 gen(rd());
  int N = 10;
  uniform_int_distribution<long long >dist(1, N);
  printf("%d\n", N);
  for (int i = 1; i <= N; ++i) {
    id[i] = i;
    sz[i] = 1;
  }
  while (sz[root(1)] != N) {
    int u = dist(gen), v = dist(gen);
    if (unite(u, v)) {
      printf("%d %d\n", u, v);
    }
  }
  return 0;
}
