#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

struct SuffLex {
  int prevlex, currlex, idx;
  bool operator==(const SuffLex &a) {
    return prevlex == a.prevlex && currlex == a.currlex;
  }
};

int cmp(const SuffLex &a, const SuffLex &b) {
  return a.prevlex == b.prevlex ? (a.currlex < b.currlex)
                                : (a.prevlex < b.prevlex);
}

vector<int> getSuffixArray(const string &s) {
  int i, stp, cnt;
  vector<int> sortIdx(s.length());
  vector<SuffLex> suffLexs(s.length());
  FOR(i, s.length()) { sortIdx[i] = s[i]; }
  for (stp = 1, cnt = 1; cnt >> 1 < s.length(); ++stp, cnt <<= 1) {
    FOR(i, s.length()) {
      suffLexs[i].prevlex = sortIdx[i];
      suffLexs[i].currlex = i + cnt < s.length() ? sortIdx[i + cnt] : -1;
      suffLexs[i].idx = i;
    }
    sort(suffLexs.begin(), suffLexs.end(), cmp);
    FOR(i, s.length())
    sortIdx[suffLexs[i].idx] = i > 0 && suffLexs[i] == suffLexs[i - 1]
                                   ? sortIdx[suffLexs[i - 1].idx]
                                   : i;
  }
  vector<int> suffixArray(suffLexs.size(), 0);
  FOR(i, suffixArray.size()) suffixArray[i] = suffLexs[i].idx;
  return suffixArray;
}

vector<int> getLCPArray(const string &s, const vector<int> &suffixArray) {
  int i, j, k, n = suffixArray.size();
  vector<int> res(n, 0);
  vector<int> invSuffixArray(n);
  FOR(i, n) { invSuffixArray[suffixArray[i]] = i; }
  k = 0;
  FOR(i, n) {
    if (invSuffixArray[i] == n - 1) {
      k = 0;
    } else {
      j = suffixArray[invSuffixArray[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
      res[invSuffixArray[i] + 1] = k;
      if (k) --k;
    }
  }
  return res;
}

char solve(const string &s, const ll &k) {
  vector<int> suffixArray = getSuffixArray(s);
  vector<int> lcpArray = getLCPArray(s, suffixArray);
  ll idx = 0;
  int si, i, j;
  FOR(si, suffixArray.size()) {
    for (i = suffixArray[si] + lcpArray[si]; i < s.length(); ++i) {
      if (idx + i - suffixArray[si] + 1 < k)
        idx += i - suffixArray[si] + 1;
      else
        for (j = suffixArray[si]; j < s.length(); ++j)
          if (++idx == k) return s[j];
    }
  }
  return (char)0;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    ll k;
    cin >> k;
    cout << solve(s, k) << endl;
  }
  return 0;
}
