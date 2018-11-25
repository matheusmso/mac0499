#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3f;

const int NEUTRAL = 0;

const int N = (int)1e5+7;
int n, q, t;
lint segtree[4*N], lazy[4*N];

lint join(lint a, lint b) {
  return a + b;
}

void app(int node, lint l, lint r, lint x){
	lazy[node] += x;
	segtree[node] += (r - l) * x;
}

void shift(int node, lint l, lint r) {
  lint mid = (l + r)/2;
  if (lazy[node] != 0) {
    app(2*node, l, mid, lazy[node]);
    app(2*node+1, mid, r, lazy[node]);
  }
  lazy[node] = 0;
}

void update(int x, int y, lint value, int node = 1, lint l = 0, lint r = n) {
  if (x >= r || y <= l) return;
  if (x <= l && y >= r) {
    app(node, l, r, value);
    return;
  }
  shift(node, l, r);
  lint mid = (l + r)/2;
  update(x, y, value, 2*node, l, mid);
  update(x, y, value, 2*node+1, mid, r);
  segtree[node] = join(segtree[2*node], segtree[2*node+1]);
}

lint query(int x, int y, int node = 1, lint l = 0, lint r = n) {
  if (x >= r || y <= l) return NEUTRAL;
  if (x <= l && y >= r) return segtree[node];
  shift(node, l, r);
  lint mid = (l + r)/2;
  return join(query(x, y, 2*node, l, mid), query(x, y, 2*node+1, mid, r));
}

int main() {
  scanf(" %d", &t);
  while (t--) {
    scanf(" %d %d", &n, &q);
    while (q--) {
      int o;
      lint a, b, k;
      scanf(" %d %lld %lld", &o, &a, &b);
      if (o == 0) {
        scanf(" %lld", &k);
        update(a-1, b, k);
      }
      else
        printf("%lld\n", query(a-1, b));
    }
    memset(segtree, 0, sizeof(segtree));
    memset(lazy, 0, sizeof(lazy));
  }
  return 0;
}
