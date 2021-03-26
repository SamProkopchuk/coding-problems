#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

int ans;

int solve(vector<vector<int>> & edges, int u, int from) {
  int nchildren = 0;
  FORR(e, edges[u]) {
    if (e != from) {
      int a = solve(edges, e, u);
      if (a % 2 == 0) ++ ans;
      nchildren += a;
    }
  }
  return nchildren + 1;
}

int main() {
  int n, e, i, u, v;
  cin >> n >> e;
  vector<vector<int>> edges(n);
  FOR(i, e) {
    cin >> u >> v, u--, v--;
    edges[u].push_back(v), edges[v].push_back(u);
  }
  ans = 0;
  solve(edges, 0, -1);
  cout << ans << endl;
  return 0;
}
