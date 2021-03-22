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
  int q, n, m, i, s, u, v;
  queue<int> nodeQ;
  vector<vector<int>> edges(MAXN, vector<int>(MAXN));
  vector<bool> visited(MAXN);
  vector<int> distances(MAXN);
  cin >> q;
  while (q--) {
    cin >> n >> m;
    FOR(i, n) { edges[i].clear(); }
    fill(distances.begin(), distances.end(), -1);
    fill(visited.begin(), visited.end(), false);
    FOR(i, m) {
      cin >> u >> v, --u, --v;
      edges[u].push_back(v);
      edges[v].push_back(u);
    }
    cin >> s, --s;
    nodeQ.push(s);
    distances[s] = 0;
    visited[s] = true;
    while (nodeQ.size()) {
      u = nodeQ.front();
      nodeQ.pop();
      FORR(v, edges[u]) {
        if (!visited[v]) {
          nodeQ.push(v);
          distances[v] = distances[u] + 6;
          visited[v] = true;
        }
      }
    }
    FOR(i, n) {
      if (distances[i]) cout << distances[i] << " ";
    }
    cout << endl;
  }
  return 0;
}
