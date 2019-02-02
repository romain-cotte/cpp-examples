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

int N, Q, MM;
int a[100005], segment_tree[100005];
ii queries[100005];


int build_segment_tree(int node, int lh, int rh) {
  if (lh == rh) { return segment_tree[node] = a[lh]; }
  int mid = (lh + rh) / 2;
  int r1 = build_segment_tree(2 * node + 1,    lh, mid);
  int r2 = build_segment_tree(2 * node + 2, mid+1,  rh);
  return segment_tree[node] = min(r1, r2);
}

int query(int node, int nl, int nr, int ql, int qr) {
  if (qr >= nr && ql <= nl) return segment_tree[node];

  if (ql > nr || qr < nl) return -1;
  int mid = (nl + nr) / 2;

  int q1 = query(2 * node + 1, nl   , mid, ql, qr);
  int q2 = query(2 * node + 2, mid+1,  nr, ql, qr);
  if (q1 == -1) return q2;
  if (q2 == -1) return q1;
  return min(q1, q2);
}

void update(int node, int nl, int nr, int q, int value) {
  if (q > nr || q < nl) return;
  if (nl == nr) {
    segment_tree[node] = a[q] = value;
    return;
  }
  int mid = (nl + nr) / 2;
  update(2 * node + 1, nl   , mid, q, value);
  update(2 * node + 2, mid+1,  nr, q, value);
  segment_tree[node] = min(segment_tree[2*node+1], segment_tree[2*node+2]);
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

    build_segment_tree(0, 0, N-1);

    F0(i, Q) {
      cin >> start >> end;
      queries[i] = ii(start, end);
      cout << query(0, 0, N-1, start, end) << endl;
    }

    cout << "--------" << endl;
    int idx = 3;
    int value = 100;
    printf("Updating %d to %d\n", idx, value);
    update(0, 0, N-1, idx, value);
    cout << "--------" << endl;

    F0(i, Q) {
      tie(start, end) = queries[i];
      printf("%d %d: %d\n", start, end, query(0, 0, N-1, start, end));
    }

  }

  return 0;
}
