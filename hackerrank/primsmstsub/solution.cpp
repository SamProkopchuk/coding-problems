#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

struct Edge {
  int to, wt;
};

bool greaterWeight(Edge &a, Edge &b) { return a.wt > b.wt; }

void popHeap(vector<Edge> &minHeap) {
  pop_heap(minHeap.begin(), minHeap.end(), greaterWeight);
  minHeap.pop_back();
}

void pushHeap(vector<Edge> &minHeap, Edge &e) {
  minHeap.push_back(e);
  push_heap(minHeap.begin(), minHeap.end(), greaterWeight);
}

int main() {
  ios_base::sync_with_stdio(false);
  int n, e, i;
  cin >> n >> e;
  vector<bool> visited(n, false);
  vector<vector<Edge>> adjList(n);
  int u, v, w;
  FOR(i, e) {
    cin >> u >> v >> w, --u, --v;
    adjList[u].push_back({v, w});
    adjList[v].push_back({u, w});
  }
  vector<Edge> minHeap;
  FORR(e, adjList[u]) { pushHeap(minHeap, e); }
  visited[u] = true;
  int added = 0, ans = 0;
  while (minHeap.size() && added != n - 1) {
    v = minHeap.front().to;
    w = minHeap.front().wt;
    popHeap(minHeap);
    if (!visited[v]) {
      visited[v] = true;
      ans += w;
      ++added;
      FORR(e, adjList[v]) {
        if (!visited[e.to]) {
          pushHeap(minHeap, e);
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
