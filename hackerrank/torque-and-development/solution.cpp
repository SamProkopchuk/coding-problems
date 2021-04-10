#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

const int MAXN = 1e5;
bool visited[MAXN];

int dfs(int u, vector<vector<int>> &edges) {
  visited[u] = true;
  int res = 1;
  FORR(v, edges[u]) {
    if (!visited[v]) res += dfs(v, edges);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  int q;
  cin >> q;
  while (q--) {
    fill(begin(visited), end(visited), false);
    ll n, m, c_lib, c_road, u, v, i, ans;
    cin >> n >> m >> c_lib >> c_road;
    vector<vector<int>> edges(n);
    FOR(i, m) {
      cin >> u >> v;
      --u, --v;
      edges[u].push_back(v);
      edges[v].push_back(u);
    }
    if (c_lib <= c_road)
      ans = c_lib * n;
    else {
      ans = 0;
      FOR(u, n) {
        if (!visited[u]) ans += c_lib + (dfs(u, edges) - 1) * c_road;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
