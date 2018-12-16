/**
 * Segment tree implementation
 */
#include <bits/stdc++.h>

#define _ << " " <<
#define F0(i,n) for(int i=0;i<n;i++)
#define F1(i,n) for(int i=1;i<=n;i++)
#define FI(i,n) for(int i=0;i<=n;i++)
#define SZ(x) (int)(x.size())
#define TR(x) cout << #x << " = " << x << endl
#define FE(k) get<0>(k)
#define SE(k) get<1>(k)
#define TH(k) get<2>(k)
#define NN 2005
#define INF 1E9

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<vector<int> > vvi;

int N, Q;
int a[100005];
int segment_tree[100005], interval_left[100005], interval_right[100005];
int MM;

int most_significant_bit(int n) {
  int k = 0;
  while (n >>= 1) {
    k++;
  }
  return 1 << k;
}

int build_segment_tree(int node, int lh, int rh) {
  if (lh == rh) {
    interval_left[node] = lh;
    interval_right[node] = rh;
    return segment_tree[node] = a[lh];
  }
  int mid = (lh + rh) / 2;
  int r1 = build_segment_tree(2 * node + 1,    lh, mid);
  int r2 = build_segment_tree(2 * node + 2, mid+1,  rh);
  interval_left[node] = lh;
  interval_right[node] = rh;
  return segment_tree[node] = min(r1, r2);
}

int query(int node, int lh, int rh) {
  if (lh <= interval_left[node] && interval_right[node] <= rh) return segment_tree[node];
  if (interval_right[node] < lh || rh < interval_left[node]) return -1;

  int q1 = query(2 * node + 1, lh, rh);
  int q2 = query(2 * node + 2, lh, rh);
  if (q1 == -1) return q2;
  if (q2 == -1) return q1;
  return min(q1, q2);
}

int main(int argc, const char **argv) {
  int start, end;
  set<int> endpoints;
  while (1) {
    cin >> N >> Q;
    if (!N) break;
    endpoints.clear();

    F0(i, N) {
      cin >> a[i];
    }

    int M = (most_significant_bit(N) << 2) - 1;
    FI(i, M) {
      segment_tree[i] = INF;
    }
    build_segment_tree(0, 0, N-1);

    F0(i, Q) {
      cin >> start >> end;
      cout << query(0, start, end) << endl;
    }

  }

  return 0;
}
