#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3f;

const lint NEUTRAL = -INF;

const int N = (int)1e5+7;
int n, q;
lint v[N];

struct node {
  lint bst;
  lint pre;
  lint suf;
  lint tot;
};
node segtree[4*N];

node join(node a, node b) {
  node aux;
  aux.tot = a.tot + b.tot;
  aux.bst = max({a.bst, b.bst, a.suf + b.pre});
  aux.pre = max(a.pre, a.tot+b.pre);
  aux.suf = max(b.suf, b.tot+a.suf);
  return aux;
}

void build(int no = 1, int l = 0, int r = n) {
  if (l + 1 == r) {
    segtree[no].bst = segtree[no].pre = segtree[no].suf = segtree[no].tot = v[l];
    return;
  }
  int mid = (l + r)/2;
  build(2*no, l, mid);
  build(2*no+1, mid, r);
  segtree[no] = join(segtree[2*no], segtree[2*no+1]);
}

void update(int pos, lint value, int no = 1, int l = 0, int r = n) {
  if (l + 1 == r) {
    segtree[no].bst = segtree[no].pre = segtree[no].suf = segtree[no].tot = v[pos] = value;
    return;
  }
  int mid = (l + r)/2;
  if (pos < mid)
    update(pos, value, 2*no, l, mid);
  else
    update(pos, value, 2*no+1, mid, r);
  segtree[no] = join(segtree[2*no], segtree[2*no+1]);
}

node query(int x, lint y, int no = 1, int l = 0, int r = n) {
  if (x >= r || y <= l) return {NEUTRAL, NEUTRAL, NEUTRAL, NEUTRAL};
  if (x <= l && y >= r) return segtree[no];
  int mid = (l + r)/2;
  return join(query(x, y, 2*no, l, mid), query(x, y, 2*no+1, mid, r));
}

int main() {
  scanf(" %d", &n);
  for (int i = 0; i < n; i++) {
    scanf(" %lld", v + i);
  }
  build();
  scanf(" %d", &q);
  while (q--) {
    int op, x;
    lint y;
    scanf(" %d %d %lld", &op, &x, &y);
    if (op == 1) {
      node ans = query(x - 1, y);
      printf("%lld\n", ans.bst);
    } else {
      update(x - 1, y);
    }
  }
  return 0;
}
