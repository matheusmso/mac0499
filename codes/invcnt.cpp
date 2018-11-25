#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3f;

const int NEUTRAL = 0;

const int N = (int)1e7+7;
int n, t, segtree[4*N];

int join(int a, int b) {
  return a + b;
}

void update(int pos, int value, int node = 1, int l = 0, int r = N) {
  if (l + 1 == r) {
    segtree[node]++;
    return;
  }
  int mid = (l + r)/2;
  if (pos < mid)
    update(pos, value, 2*node, l, mid);
  else
    update(pos, value, 2*node+1, mid, r);
  segtree[node] = join(segtree[2*node], segtree[2*node+1]);
}

int query(int x, int y, int node = 1, int l = 0, int r = N) {
  if (x >= r || y <= l) return NEUTRAL;
  if (x <= l && y >= r) return segtree[node];
  int mid = (l + r)/2;
  return join(query(x, y, 2*node, l, mid), query(x, y, 2*node+1, mid, r));
}

int main() {
  scanf(" %d", &t);
  while (t--) {
    scanf(" %d", &n);
    lint ans = 0;
    for (int i = 0; i < n; i++) {
      int x;
      scanf(" %d", &x);
      ans += query(x + 1, N);
      update(x, 1);
    }
    memset(segtree, 0, sizeof(segtree));
    printf("%lld\n", ans);
  }
  return 0;
}
