#include <algorithm>
#include <bitset>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <vector>

using namespace std;

namespace {

constexpr int MAX_N = 100000;

void trim_from_node(vector<map<int, int>> &graph,
                    const bitset<MAX_N> &is_machine, int node) {
  while (!is_machine[node] && graph[node].size() == 1) {
    const int next = graph[node].cbegin()->first;
    graph[node].erase(next);
    graph[next].erase(node);
    node = next;
  }
}

void trim(vector<map<int, int>> &graph, const bitset<MAX_N> &is_machine) {
  // Remove all edges that only have path to machine on one side.
  for (int node = 0; node < graph.size(); ++node) {
    trim_from_node(graph, is_machine, node);
  }
}

int64_t get_solution(vector<map<int, int>> &graph,
                     const bitset<MAX_N> &is_machine) {
  trim(graph, is_machine);

  using EdgeData = tuple<int, int, int>;
  priority_queue<EdgeData, vector<EdgeData>, greater<EdgeData>> pq;
  for (int node = 0; node < graph.size(); ++node) {
    for (const auto &it : graph[node]) {
      pq.emplace(it.second, node, it.first);
    }
  }

  int64_t total_cost = 0;
  while (!pq.empty()) {
    const auto [cost, a, b] = pq.top();
    pq.pop();
    if (graph[a].find(b) != graph[a].end()) {
      total_cost += cost;
      graph[a].erase(b);
      graph[b].erase(a);
      trim_from_node(graph, is_machine, a);
      trim_from_node(graph, is_machine, b);
    }
  }
  return total_cost;
}

} // namespace

int main() {
  int n, k;
  cin >> n >> k;
  vector<map<int, int>> graph(n);
  while (--n) {
    int u, v, t;
    cin >> u >> v >> t;
    graph[v].emplace(u, t);
    graph[u].emplace(v, t);
  }
  bitset<MAX_N> is_machine;
  while (k--) {
    int m;
    cin >> m;
    is_machine.set(m);
  }
  cout << get_solution(graph, is_machine) << endl;
  return 0;
}
