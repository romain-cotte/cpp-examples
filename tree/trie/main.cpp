#include <bits/stdc++.h>
using namespace std;
const int maxn = 3000005;
int child[maxn][2], val[maxn];
int q, sz=1;
string op;

void _insert(int x) {
  int pos = 0;
  for (int i=29; i>=0; --i) {
    int id = (x>>i)&1;
    if (!child[pos][id])
      child[pos][id] = sz++;
    pos = child[pos][id];
    printf("pos %d\n", pos);
    ++val[pos];
  }
}

void _delete(int x) {
  int pos = 0;
  for (int i=29; i>=0; --i) {
    int id = (x>>i)&1;
    pos = child[pos][id];
    --val[pos];
  }
}

int query(int x) {
  int ans=0, pos=0;
  for (int i=29; i>=0; --i) {
    int id = (x>>i)&1;
    if (id == 1) {
      if (child[pos][0] && val[child[pos][0]]) {
        ans += 1<<i;
        pos = child[pos][0];
      }
      else
        pos = child[pos][1];
    }
    else{
      if (child[pos][1] && val[child[pos][1]]) {
        ans += 1<<i;
        pos = child[pos][1];
      }
      else
        pos = child[pos][0];
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> q;
  int num;
  _insert(0);
  while (q--) {
    cin >> op >> num;
    if (op[0] == '+')
      _insert(num);
    else if (op[0] == '-')
      _delete(num);
    else
      cout << query(num) << endl;
  }
  return 0;
}
