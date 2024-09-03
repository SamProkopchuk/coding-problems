#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace {

constexpr int Ord(char c) { return c - 'a'; }

void solve(const vector<string> &words) {
  vector<map<char, int>> trie(1);
  for (const auto &word : words) {
    int curr_node_idx = 0;
    bool common_prefix = true;
    for (int i = 0; i < word.size(); ++i) {
      const char &c = word[i];
      const auto &it = trie[curr_node_idx].find(c);
      if ((i == word.size() - 1 && it != trie[curr_node_idx].end()) ||
          (i != 0 && common_prefix && trie[curr_node_idx].size() == 0)) {
        // Current word is prefix of prev one, or prev one is prefix of current.
        cout << "BAD SET" << endl;
        cout << word << endl;
        return;
      }
      if (it != trie[curr_node_idx].end()) {
        curr_node_idx = it->second;
        continue;
      }
      trie[curr_node_idx][c] = trie.size();
      curr_node_idx = trie.size();
      trie.push_back({});
      common_prefix = false;
    }
  }
  cout << "GOOD SET" << endl;
}

} // namespace

int main() {
  int n;
  cin >> n;
  vector<string> words(n);
  for (auto &word : words) {
    cin >> word;
  }
  solve(words);
}
