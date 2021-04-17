#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  size_t n, m, u, v, i, j, k;
  cin >> n >> m;
  int adj[n][n];
  FOR(i, n) {
    FOR(j, n) { adj[i][j] = (i == j) ? 0 : -1; }
  }
  FOR(i, m) {
    int w;
    cin >> u >> v >> w;
    adj[--u][--v] = w;
  }
  FOR(k, n) {
    FOR(i, n) {
      FOR(j, n) {
        if (adj[i][k] != -1 && adj[k][j] != -1)
          adj[i][j] = (adj[i][j] == -1) ? adj[i][k] + adj[k][j]
                                        : min(adj[i][j], adj[i][k] + adj[k][j]);
      }
    }
  }
  size_t q;
  cin >> q;
  while (q--) {
    cin >> u >> v;
    cout << adj[--u][--v] << endl;
  }
  return 0;
}
