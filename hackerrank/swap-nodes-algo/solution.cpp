#include <iostream>
#include <vector>

using namespace std;

namespace {

constexpr int kNullNode = -1;

void swap_children(vector<pair<int, int>> &children, const int k, const int i,
                   const int depth) {
  pair<int, int> &node = children[i];
  if (node.first != kNullNode) {
    swap_children(children, k, node.first, depth + 1);
  }
  if (node.second != kNullNode) {
    swap_children(children, k, node.second, depth + 1);
  }
  if (depth % k == 0) {
    swap(node.first, node.second);
  }
}

void traverse(const vector<pair<int, int>> &children, vector<int> &traversal,
              const int i) {
  const pair<int, int> &node = children[i];
  if (node.first != kNullNode) {
    traverse(children, traversal, node.first);
  }
  traversal.push_back(i + 1);
  if (node.second != kNullNode) {
    traverse(children, traversal, node.second);
  }
}

vector<int> get_solution(vector<pair<int, int>> &children, const int k) {
  swap_children(children, k, 0, 1);
  vector<int> traversal;
  traversal.reserve(children.size());
  traverse(children, traversal, 0);
  return traversal;
}

} // namespace

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> children;
  children.reserve(n);
  for (int i = 0; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    if (a != kNullNode) {
      --a;
    }
    if (b != kNullNode) {
      --b;
    }
    children.emplace_back(a, b);
  }
  int q;
  cin >> q;
  while (q--) {
    int k;
    cin >> k;
    vector<int> traversal = get_solution(children, k);
    for (const int &i : traversal) {
      cout << i << ' ';
    }
    cout << endl;
  }
  return 0;
}
