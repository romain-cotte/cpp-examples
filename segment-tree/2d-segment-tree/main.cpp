/**
 * 2d segment tree
 */
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdio.h>

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
#define NN 1000005
using namespace std;

template<typename T> void remin(T& a, const T& b) { if (b < a) a = b; }
template<typename T> void remax(T& a, const T& b) { if (b > a) a = b; }

int N;

int mat[4][4] = {
  {1, 2, 3, 4},
  {0, 9, 2, 1},
  {0, 2, 3, 4},
  {0, 1, 2, 4},
};

int segment_tree[505][1105];
int final_segtree[1105][1105];

void build_segment_tree(int l, int node, int start, int end) {
  if (start == end) {
    segment_tree[l][node] = mat[l][start];
    // printf("[%d][%d] %d\n", l, node, mat[l][start]);
    return;
  }
  int mid = (start + end) / 2;
  build_segment_tree(l, 2*node+1, start  , mid);
  build_segment_tree(l, 2*node+2, mid + 1, end);
  segment_tree[l][node] = segment_tree[l][2*node+1] + segment_tree[l][2*node+2];
}

void build_final_segtree(int node, int low, int high) {
  if (low == high) {
    for (int k = 0; k <= 2*N; ++k) {
      final_segtree[node][k] = segment_tree[low][k];
    }
    return;
  }

  int mid = (low + high) / 2;
  build_final_segtree(2*node + 1,   low, mid);
  build_final_segtree(2*node + 2, mid+1, high);
  for (int k = 0; k <= 2*N; ++k) {
    final_segtree[node][k] = final_segtree[2*node+1][k] + final_segtree[2*node+2][k];
  }
}

int final_query(int idx, int node, int start, int end, int x1, int x2) {
  if (start > x2 || end < x1) return 0;
  if (x1 <= start && end <= x2) return final_segtree[idx][node];
  int mid = (start + end) / 2;
  int r1 = final_query(idx, 2*node+1, start, mid, x1, x2);
  int r2 = final_query(idx, 2*node+2, mid+1, end, x1, x2);
  return r1 + r2;
}

int query(int node, int start, int end, int x1, int y1, int x2, int y2) {
  if (y2 < start || end < y1) return 0;
  if (y1 <= start && end <= y2) {
    return final_query(node, 0, 0, N-1, x1, x2);
  }

  int mid = (start + end) / 2;
  int r1 = query(2*node+1, start, mid, x1, y1, x2, y2);
  int r2 = query(2*node+2, mid+1, end, x1, y1, x2, y2);
  return r1 + r2;
}

void final_update(int idx, int node, int start, int end, int x, int v) {
  if (x < start || end < x) return;
  if (start == end) {
    final_segtree[idx][node] = v;
    return;
  }
  int mid = (start + end) / 2;
  final_update(idx, 2*node + 1, start, mid, x, v);
  final_update(idx, 2*node + 2, mid+1, end, x, v);
  final_segtree[idx][node] = final_segtree[idx][2*node+1] + final_segtree[idx][2*node+2];
  printf("[%d][%d] %d\n", idx, node, final_segtree[idx][node]);
}

void update(int node, int start, int end, int x, int y, int v) {
  if (y < start || end < y) return;
  if (start == end) {
    final_update(node, 0, 0, N-1, x, v);
    return;
  }
  int mid = (start + end) / 2;
  update(2*node+1, start, mid, x, y, v);
  update(2*node+2, mid+1, end, x, y, v);
  for (int k = 0; k <= 2*N; ++k) {
    final_segtree[node][k] = final_segtree[2*node+1][k] + final_segtree[2*node+2][k];
  }
}


int main(int argc, const char **argv) {
  scanf("%d", &N);

  // F0(i, N) {
  //   F0(j, N) {
  //     scanf("%d", &mat[i][j]);
  //   }
  // }

  F0(i, N) build_segment_tree(i, 0, 0, N-1);
  build_final_segtree(0, 0, N-1);

  int x1, y1, x2, y2;
  x1 = 0; y1 = 0; x2 = 0; y2 = 0;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 1);
  x1 = 0; y1 = 0; x2 = 1; y2 = 0;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 3);
  x1 = 0; y1 = 0; x2 = 2; y2 = 0;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 6);
  x1 = 0; y1 = 0; x2 = 3; y2 = 0;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 10);
  x1 = 3; y1 = 0; x2 = 3; y2 = 0;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 4);


  x1 = 0; y1 = 1; x2 = 0; y2 = 1;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 0);
  x1 = 0; y1 = 1; x2 = 1; y2 = 1;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 9);
  x1 = 0; y1 = 1; x2 = 2; y2 = 1;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 11);
  x1 = 0; y1 = 1; x2 = 3; y2 = 1;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 12);


  x1 = 1; y1 = 1; x2 = 2; y2 = 3;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 19);

  x1 = 0; y1 = 0; x2 = 3; y2 = 3;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 38);
  // printf("%d\n", query(0, 0, N-1, x1, y1, x2, y2));

  F0(i, 2*N+1) {
    printf("%d ", final_segtree[0][i]);
  }
  printf("\n");
  update(0, 0, N-1, 0, 0, 100);
  F0(i, 2*N+1) {
    printf("%d ", final_segtree[0][i]);
  }
  printf("\n");

  x1 = 0; y1 = 0; x2 = 0; y2 = 0;
  printf("%d\n", query(0, 0, N-1, x1, y1, x2, y2));
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 100);
  x1 = 0; y1 = 0; x2 = 1; y2 = 0;
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 102);

  x1 = 0; y1 = 0; x2 = 3; y2 = 3;
  printf("%d\n", query(0, 0, N-1, x1, y1, x2, y2));
  assert(query(0, 0, N-1, x1, y1, x2, y2) == 137);
}
