#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// Mod without possible negative return value.
int mod(int a, int b) { return (a % b + b) % b; }

vector<int> get_pattern_idxs(string s, string p) {
  vector<int> pattern_idxs;
  if (s.length() < p.length() || p.length() == 0) return pattern_idxs;

  int q = 73;  // https://www.google.com/search?q=coolest+prime+number
  int d = numeric_limits<char>::max();
  int sh = 0;
  int ph = 0;
  int h = 1;
  int i;

  for (i = 0; i < p.length() - 1; i++) h = mod(h * d, q);
  for (i = 0; i < p.length(); i++) ph = mod(ph * d + p[i], q);
  for (i = 0; i < s.length(); i++) {
    sh = mod((sh - ((i >= p.length()) ? s[i - p.length()] * h : 0)) * d + s[i], q);
    if (sh == ph && i + 1 >= p.length() &&
        p.compare(s.substr(i - p.length() + 1, p.length())) == 0)
      pattern_idxs.push_back(i + 1 - p.length());
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
