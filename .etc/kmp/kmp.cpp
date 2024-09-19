#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> get_lps(const string &s) {
  vector<int> lps(s.length());
  lps[0] = 0;

  for (int i = 1; i < s.length(); ++i) {
    int j = lps[i - 1];
    while (j > 0 && s[i] != s[j])
      j = lps[j - 1];
    if (s[i] == s[j])
      ++j;
    lps[i] = j;
  }

  return lps;
}

vector<int> get_pattern_idxs(const string &s, const string &p) {
  vector<int> pattern_idxs;
  if (s.length() < p.length() || p.length() == 0)
    return pattern_idxs;

  vector<int> lps = get_lps(p);
  cout << "LPS: ";
  for (int i : lps)
    cout << i << " ";
  cout << endl;

  int i = 0, j = 0;
  while (i < s.length()) {
    if (s[i] == p[j]) {
      ++i;
      ++j;
      if (j == p.length()) {
        pattern_idxs.push_back(i - p.length());
        j = lps[j - 1];
      }
    } else {
      if (j > 0) {
        j = lps[j - 1];
      } else {
        ++i;
      }
    }
  }

  return pattern_idxs;
}

int main() {
  string s;
  string p;
  cin >> s >> p;

  vector<int> pattern_idxs = get_pattern_idxs(s, p);

  for (int i : pattern_idxs)
    cout << "Found pattern at index " << i << endl;

  return 0;
}
