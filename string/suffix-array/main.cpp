/**
 *
 */
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>

#define SZ(x) (int)(x.size())
#define F0(i,n) for(int i=0;i<n;i++)
#define F1(i,n) for(int i=1;i<=n;i++)
#define FI(i,n) for(int i=0;i<=n;i++)
#define TR(x) cout << #x << " = " << x << endl
#define FE(k) get<0>(k)
#define SE(k) get<1>(k)
#define TH(k) get<2>(k)
#define _ << " " <<
#define INF 1E9
#define NN 10000

using namespace std;
typedef vector<int> vi;

template<typename T> void remin(T& a, const T& b) { if (b < a) a = b; }
template<typename T> void remax(T& a, const T& b) { if (b > a) a = b; }

int RA[NN], SA[NN], LCP[NN], *FC, *SC, step, N;
char S[NN], Q[NN];


bool cmp(int i, int j) {
  // printf("%d %d\n", i, j);
  if (step == -1 || FC[i] != FC[j]) return FC[i] < FC[j];
  return FC[i + (1 << step)] < FC[j + (1 << step)];
}

int main(int argc, const char **argv) {
  scanf("%s", S);
  N = strlen(S);
  printf("%s\n", S);

  for (int i = 0; i < N; ++i) RA[i] = S[SA[i] = i];

  // for (int i = 0; i < N; ++i) {
  //   printf("%d\n", RA[i]);
  // }

  for (FC = RA, SC = LCP, step = -1; (1<<step) < N; ++step) {
    printf("\n== Step: %d ==\n", step);
    sort(SA, SA + N, cmp);

    int cnt = 0;
    for (int i = 0; i < N; ++i) {
      if (i > 0 && cmp(SA[i-1], SA[i])) ++cnt; // character changement
      SC[SA[i]] = cnt;
    }
    // printf("FC[SA[0]] %d\n", FC[SA[0]]);
    // printf("FC[SA[0]] %d\n", FC[SA[1]]);

    cout << ":::" << (FC[SA[0]] < FC[SA[1]]) << endl;

    printf("        SA  FC =SC:\n");
    for (int i = 0; i < N; ++i) {
      printf("%7s %2d %3d  %2d\n", S + SA[i], SA[i], FC[SA[i]], SC[SA[i]]);
    }

    printf("cnt: %d\n", cnt);

    if (cnt == N-1) break; // all distinct, no need to continue
    swap(FC, SC);
  }

  for (int i = 0; i < N; ++i) {
    RA[SA[i]] = i;
  }

  for (int i = 0; i < N; ++i) {
    printf("%s\n", S + SA[i]);
  }

  return 0;
}
