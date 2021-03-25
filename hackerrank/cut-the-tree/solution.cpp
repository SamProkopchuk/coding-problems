#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

const int MAXN = 1e5;
int data[MAXN];
bool visited[MAXN];
ll total;

ll queryNodeExcluding(vector<vector<pair<int, ll>>> &edges, int u, int v) {
  ll res = 0;
  FORR(e, edges[u]) {
    if (e.first != v) res += e.second;
  }
  return res + data[u];
}

void calcCutSums(vector<vector<pair<int, ll>>> &edges, int u) {
  visited[u] = true;
  FORR(e, edges[u]) {
    if (!visited[e.first]) calcCutSums(edges, e.first);
  }
  FORR(e, edges[u]) { e.second = queryNodeExcluding(edges, e.first, u); }
}

int main() {
  int n, i, u, v;
  cin >> n;
  vector<vector<pair<int, ll>>> edges(n);
  total = 0;
  FOR(i, n) cin >> data[i], total += data[i];
  FOR(i, n - 1) {
    cin >> u >> v, --u, --v;
    edges[u].push_back({v, 0}), edges[v].push_back({u, 0});
  }
  fill(begin(visited), end(visited), false);
  calcCutSums(edges, u);
  ll res = LLONG_MAX;
  FOR(i, n) {
    FORR(e, edges[i]) { res = min(res, abs(total - 2 * e.second)); }
  }
  cout << res << endl;
  return 0;
}
