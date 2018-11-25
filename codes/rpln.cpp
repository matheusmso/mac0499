#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3f;

const int NEUTRAL = INF;

const int N = (int)1e5+7;
int n, q, t, v[N], segtree[4*N];

int join(int a, int b) {
  return min(a, b);
}

void build(int node = 1, int l = 0, int r = n) {
  if (l + 1 == r) {
    segtree[node] = v[l];
    return;
  }
  int mid = (l + r)/2;
  build(2*node, l, mid);
  build(2*node+1, mid, r);
  segtree[node] = join(segtree[2*node], segtree[2*node+1]);
}

int query(int x, int y, int node = 1, int l = 0, int r = n) {
  if (x >= r || y <= l) return NEUTRAL;
  if (x <= l && y >= r) return segtree[node];
  int mid = (l + r)/2;
  return join(query(x, y, 2*node, l, mid), query(x, y, 2*node+1, mid, r));
}

int main() {
  scanf(" %d", &t);
  int sce = 1;
  while (t--) {
    printf("Scenario #%d:\n", sce++);
    scanf(" %d %d", &n, &q);
    for (int i = 0; i < n; i++) {
      scanf(" %d", v + i);
    }
    build();
    for (int i = 0; i < q; i++) {
      int x, y;
      scanf(" %d %d", &x, &y);
      printf("%d\n", query(x - 1, y));
    }
  }
  return 0;
}
