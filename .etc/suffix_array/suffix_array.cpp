#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Suffix array O(n log^2 n) implementation using prefix doubling.

using namespace std;

struct SuffLex {
  int prevlex, currlex, idx;
  bool operator==(SuffLex a) {
    return prevlex == a.prevlex && currlex == a.currlex;
  }
};

int cmp(SuffLex a, SuffLex b) {
  return a.prevlex == b.prevlex ? (a.currlex < b.currlex)
                                : (a.prevlex < b.prevlex);
}

vector<int> get_suffix_array(string s) {
  int i, stp, cnt;

  vector<int> sort_idx(s.length(), 0);
  vector<SuffLex> suff_lexs(s.length());

  for (i = 0; i < s.length(); i++) sort_idx[i] = s[i];
  for (stp = 1, cnt = 1; cnt >> 1 < s.length(); stp++, cnt <<= 1) {
    for (i = 0; i < s.length(); i++) {
      suff_lexs[i].prevlex = sort_idx[i];
      suff_lexs[i].currlex = i + cnt < s.length() ? sort_idx[i + cnt] : -1;
      suff_lexs[i].idx = i;
    }
    sort(suff_lexs.begin(), suff_lexs.end(), cmp);
    for (i = 0; i < s.length(); i++)
      sort_idx[suff_lexs[i].idx] = i > 0 && suff_lexs[i] == suff_lexs[i - 1]
                                       ? sort_idx[suff_lexs[i - 1].idx]
                                       : i;
  }

  vector<int> suffix_array(suff_lexs.size(), 0);
  for (i = 0; i < suffix_array.size(); i++) suffix_array[i] = suff_lexs[i].idx;

  return suffix_array;
}

int main() {
  string s;
  cin >> s;

  vector<int> suffix_array = get_suffix_array(s);

  for (int idx : suffix_array) cout << "|" << idx;
  cout << "|" << endl;

  return 0;
}
