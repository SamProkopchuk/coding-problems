#include <iostream>
#include <queue>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1000;

int main() {
  ios_base::sync_with_stdio(false);
  queue<int> nodeQ;
  vector<vector<int>> edges(MAXN, vector<int>(MAXN));
  vector<bool> visited(MAXN);
  vector<int> dist(MAXN);
  int q;
  cin >> q;
  while (q--) {
    int n, m, u, v, i;
    fill(dist.begin(), dist.end(), -1);
    fill(visited.begin(), visited.end(), false);
    cin >> n >> m;
    FOR(i, n) { edges[i].clear(); }
    FOR(i, m) {
      cin >> u >> v, --u, --v;
      edges[u].push_back(v);
      edges[v].push_back(u);
    }
    cin >> u, --u;
    visited[u] = true;
    dist[u] = 0;
    nodeQ.push(u);
    while (nodeQ.size()) {
      u = nodeQ.front();
      nodeQ.pop();
      FORR(v, edges[u]) {
        if (!visited[v]) {
          visited[v] = true;
          dist[v] = dist[u] + 6;
          nodeQ.push(v);
        }
      }
    }
    FOR(i, n) {
      if (dist[i]) cout << dist[i] << ' ';
    }
    cout << endl;
  }
  return 0;
}
