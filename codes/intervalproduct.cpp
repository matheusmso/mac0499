#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3f;

const int NEUTRAL = 0;

const int N = (int)1e5+7;
int n, k, v[N], segz[4*N], segn[4*N];

int join(int a, int b) {
  return a + b;
}

void build(int node = 1, int l = 0, int r = n) {
  if (l + 1 == r) {
    if (v[l] == 0)
      segz[node] = 1;
    else if (v[l] < 0)
      segn[node] = 1;
    else
      segz[node] = segn[node] = 0;
    return;
  }
  int mid = (l + r)/2;
  build(2*node, l, mid);
  build(2*node+1, mid, r);
  segn[node] = join(segn[2*node], segn[2*node+1]);
  segz[node] = join(segz[2*node], segz[2*node+1]);
}

void update(int pos, int value, int node = 1, int l = 0, int r = n) {
  if (value > 0) {
    segn[node] -= v[pos] < 0;
    segz[node] -= v[pos] == 0;
  }
  else if (value < 0) {
    segn[node] += v[pos] >= 0;
    segz[node] -= v[pos] == 0;
  }
  else {
    segn[node] -= v[pos] < 0;
    segz[node] += v[pos] != 0;
  }
  if (l + 1 == r) {
    v[pos] = value;
    return;
  }
  int mid = (l + r)/2;
  if (pos < mid)
    update(pos, value, 2*node, l, mid);
  else
    update(pos, value, 2*node+1, mid, r);
  segz[node] = join(segz[2*node], segz[2*node+1]);
  segn[node] = join(segn[2*node], segn[2*node+1]);
}

int queryz(int x, int y, int node = 1, int l = 0, int r = n) {
  if (x >= r || y <= l) return NEUTRAL;
  if (x <= l && y >= r) return segz[node];
  int mid = (l + r)/2;
  return join(queryz(x, y, 2*node, l, mid), queryz(x, y, 2*node+1, mid, r));
}

int queryn(int x, int y, int node = 1, int l = 0, int r = n) {
  if (x >= r || y <= l) return NEUTRAL;
  if (x <= l && y >= r) return segn[node];
  int mid = (l + r)/2;
  return join(queryn(x, y, 2*node, l, mid), queryn(x, y, 2*node+1, mid, r));
}

int main() {
  while (scanf(" %d %d", &n, &k) != EOF) {
    for (int i = 0; i < n; i++) {
      scanf(" %d", v + i);
    }
    memset(segz, 0, sizeof(segz));
    memset(segn, 0, sizeof(segn));
    build();
    while (k--) {
      int x, y;
      char c;
      scanf(" %c %d %d", &c, &x, &y);
      if (c == 'C') update(x - 1, y);
      else {
        int z = queryz(x - 1, y);
        int neg = queryn(x - 1, y);
        if (z) printf("0");
        else printf("%s", neg % 2 == 0 ? "+" : "-");
      }
    }
    printf("\n");
  }
  return 0;
}
