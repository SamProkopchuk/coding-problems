#include <math.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct suffit {
  int prvlex, curlex, idx;
};

int cmp(suffit a, suffit b) {
  return a.prvlex == b.prvlex ? (a.curlex < b.curlex ? 1 : 0)
                              : (a.prvlex < b.prvlex ? 1 : 0);
}

int diff(suffit a, suffit b) {
  return a.prvlex == b.prvlex ? (b.curlex - a.curlex) : (b.prvlex - a.prvlex);
}

int main() {
  int i, stp, cnt;

  string s;
  cin >> s;

  int sort_idx_table[(int) log2((float) s.length()) + 2][s.length()];

  cout << (int) log2((float) s.length()) + 2 << endl;

  vector<suffit> suffits(s.length());

  for (i = 0; i < s.length(); i++) sort_idx_table[0][i] = s[i];
  for (stp = 1, cnt = 1; cnt >> 1 < s.length(); stp++, cnt <<= 1) {
    for (i = 0; i < s.length(); i++) {
      suffits[i].prvlex = sort_idx_table[stp - 1][i];
      suffits[i].curlex =
          i + cnt < s.length() ? sort_idx_table[stp - 1][i + cnt] : -1;
      suffits[i].idx = i;
    }
    sort(suffits.begin(), suffits.end(), cmp);
    for (i = 0; i < s.length(); i++) {
      sort_idx_table[stp][suffits[i].idx] =
          i > 0 && diff(suffits[i], suffits[i - 1]) == 0
              ? sort_idx_table[stp][suffits[i].idx]
              : i;
    }
  }

  for (i=0; i<s.length(); i++) {
  	cout << sort_idx_table[stp-1][i] << endl;
  }

  return 0;
}