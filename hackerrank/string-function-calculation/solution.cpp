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
    FOR(i, s.length()) {
      sortIdx[suffLexs[i].idx] = i > 0 && suffLexs[i] == suffLexs[i - 1]
                                     ? sortIdx[suffLexs[i - 1].idx]
                                     : i;
    }
  }
  FOR(i, sortIdx.size()) { sortIdx[i] = suffLexs[i].idx; }
  return sortIdx;
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

int main() {
  string s;
  cin >> s;
  vector<int> suffixArray = getSuffixArray(s);
  vector<int> lcpArray = getLCPArray(s, suffixArray);
  lcpArray.push_back(-1);
  stack<int> stk;
  int i, j;
  ll ans = s.size();
  FOR(i, lcpArray.size()) {
    while (!stk.empty() && lcpArray[j = stk.top()] > lcpArray[i]) {
      stk.pop();
      ans = max(ans, (ll)lcpArray[j] * (stk.empty() ? i + 1 : (i - stk.top())));
    }
    stk.push(i);
  }
  cout << ans << endl;
  return 0;
}
