#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> get_lps(string p) {
  vector<int> lps(p.length(), 0);

  // Length of previous string that's a proper prefix and suffix
  int len = 0;
  int i = 1;
  while (i < p.length()) {
    if (p[i] == p[len]) {
      len++;
      lps[i] = len;
      i++;
    } else if (len != 0) {
      // See https://www.youtube.com/watch?v=tWDUjkMv6Lc
      // For detailed explanation.
      len = lps[len - 1];  // Actual big brain juicer Pog.
    } else {
      i++;
    }
  }

  return lps;
}

vector<int> get_pattern_idxs(string s, string p) {
  vector<int> pattern_idxs;
  if (p.length() == 0) return pattern_idxs;

  vector<int> lps = get_lps(p);

  int i = 0, j = 0;
  while (i < s.length()) {
    if (s[i] == s[j]) {
      i++;
      j++;
      if (j == p.length()) {
        pattern_idxs.push_back(i - j);
        j = lps[j - 1];
      }
    } else if (j == 0) {
      i++;
    } else {
      j = lps[j - 1];
    }
  }

  return pattern_idxs;
}

int main() {
  string s;
  string p;
  cin >> s >> p;

  vector<int> pattern_idxs = get_pattern_idxs(s, p);

  for (int i : pattern_idxs) cout << "Found pattern at index " << i << endl;

  return 0;
}
