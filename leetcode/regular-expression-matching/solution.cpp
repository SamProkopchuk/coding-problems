#include <cassert>
#include <iostream>
#include <set>
#include <stack>
#include <string>

using namespace std;

using State = pair<int, int>;

constexpr bool match(const char c, const char m) { return m == '.' || c == m; }

inline void addIfNotVisited(stack<State> &stk, set<State> &visited,
                            State &&state) {
  if (visited.find(state) == visited.end()) {
    stk.emplace(state);
    visited.emplace(state);
  }
}

class Solution {
public:
  static bool isMatch(string s, string p) {
    set<State> visited;
    stack<State> stk;
    stk.emplace(State{});
    while (!stk.empty()) {
      const auto [i, j] = stk.top();
      stk.pop();
      if (j == p.size()) {
        if (i == s.size()) {
          return true;
        }
        continue;
      }
      assert(p[j] != '*');
      if (j + 1 < p.size() && p[j + 1] == '*') {
        int it = i;
        do {
          addIfNotVisited(stk, visited, {it, j + 2});
        } while (it < s.size() && match(s[it++], p[j]));
      } else if (i < s.size() && match(s[i], p[j])) {
        addIfNotVisited(stk, visited, {i + 1, j + 1});
      }
    }
    return false;
  }
};

int main() {
  string s, p;
  cin >> s;
  cin >> p;
  cout << "isMatch?: " << Solution::isMatch(s, p) << endl;
  return 0;
}
