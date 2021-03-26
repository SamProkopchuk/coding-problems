#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

struct edge {
  int u, v, w;
};

bool cmp(edge &a, edge &b) { return a.w < b.w ? true : false; }

int getParent(vector<int> &disjoint, int u) {
  int v = u;
  while (disjoint[v] != v) v = disjoint[v];
  while (disjoint[u] != u) {
    int t = disjoint[u];
    disjoint[u] = v;
    u = t;
  }
  return v;
}

int main() {
  int n, e, i;
  cin >> n >> e;
  vector<int> disjoint(n);
  FOR(i, n) { disjoint[i] = i; }
  vector<edge> edges(e);
  FOR(i, e) {
    cin >> edges[i].u >> edges[i].v >> edges[i].w, --edges[i].u, --edges[i].v;
  }
  sort(edges.begin(), edges.end(), cmp);
  ll ans = 0;
  int addedEdges = 0;
  FORR(e, edges) {
    if (getParent(disjoint, e.u) != getParent(disjoint, e.v))
      disjoint[getParent(disjoint, e.u)] = getParent(disjoint, e.v), ans += e.w,
                                   ++addedEdges;
    if (addedEdges == n - 1) break;
  }
  cout << ans << endl;
  return 0;
}
