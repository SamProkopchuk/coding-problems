#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

const int MAXN = 1e5;
bool visited[MAXN];
ll distances[MAXN];

void dfs(const set<int> &letters, const vector<map<int, int>> &edges,
         const int u, const ll d = 0) {
  visited[u] = true;
  if (letters.count(u)) distances[u] = d;
  FORR(vd, edges[u]) {
    if (!visited[vd.first]) dfs(letters, edges, vd.first, d + vd.second);
  }
}

void prune(const set<int> &letters, vector<map<int, int>> &edges, const int u) {
  if (!letters.count(u) && edges[u].size() == 1) {
    int v, d;
    v = (*edges[u].begin()).first;
    d = (*edges[u].begin()).second;
    edges[u].clear();
    edges[v].erase(u);
    prune(letters, edges, v);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int i, n, k, l, u, v, d;
  cin >> n >> k;
  vector<map<int, int>> edges(n);
  set<int> letters;
  FOR(i, k) {
    cin >> l;
    letters.insert(--l);
  }
  FOR(i, n - 1) {
    cin >> u >> v >> d;
    --u, --v;
    edges[u][v] = d;
    edges[v][u] = d;
  }
  FOR(i, n) { prune(letters, edges, i); }
  u = *letters.begin();
  fill(begin(visited), end(visited), false);
  dfs(letters, edges, u);
  ll diameter = 0;
  FORR(letter, letters) {
    if (distances[letter] > diameter) {
      diameter = distances[letter];
      v = letter;
    }
  }
  fill(begin(visited), end(visited), false);
  dfs(letters, edges, v);
  FORR(letter, letters) {
    if (distances[letter] > diameter) diameter = distances[letter];
  }
  ll doubleWeight = 0;
  FORR(edgeSet, edges) {
    FORR(vd, edgeSet) { doubleWeight += vd.second; }
  }
  cout << doubleWeight - diameter << endl;
  return 0;
}
