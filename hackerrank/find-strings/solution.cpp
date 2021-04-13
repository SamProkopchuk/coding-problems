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
  vector<int> lcpArray(n, 0);
  vector<int> invSuffixArray(n);
  FOR(i, n) { invSuffixArray[suffixArray[i]] = i; }
  k = 0;
  FOR(i, n) {
    if (invSuffixArray[i] == n - 1) {
      k = 0;
    } else {
      j = suffixArray[invSuffixArray[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
      lcpArray[invSuffixArray[i] + 1] = k;
      if (k) --k;
    }
  }
  return lcpArray;
}

string getKthSubstring(const string &s, const vector<int> &suffixArray,
                       const vector<int> &lcpArray,
                       const vector<int> &subIdxLookup,
                       const vector<int> &subLenLookup, const int &k) {
  int idx = 0;
  for (int si=0; si < suffixArray.size(); ++si) {
    int subIdx = subIdxLookup[suffixArray[si]];
    int subLen = subLenLookup[suffixArray[si]];
    if (idx + subLen - subIdx - lcpArray[si] < k)
      idx += subLen - subIdx - lcpArray[si];
    else {
      int end = lcpArray[si] + k - idx;
      return s.substr(suffixArray[si], end);
    }
  }
  return "INVALID";
}

int main() {
  int i, n;
  cin >> n;
  string s;
  s.reserve(1e5 + 50);
  vector<int> subIdxLookup, subLenLookup;
  subIdxLookup.reserve(1e5 + 50);
  subLenLookup.reserve(1e5 + 50);
  FOR(i, n) {
    string temp;
    int idx;
    cin >> temp;
    s.append(temp + (char)(i + 1));
    FOR(idx, temp.length() + 1) {
      subIdxLookup.push_back(idx);
      subLenLookup.push_back(temp.length());
    }
  }
  vector<int> suffixArray = getSuffixArray(s);
  vector<int> lcpArray = getLCPArray(s, suffixArray);
  int q, k;
  cin >> q;
  while (q--) {
    cin >> k;
    cout << getKthSubstring(s, suffixArray, lcpArray, subIdxLookup,
                            subLenLookup, k)
         << endl;
  }
  return 0;
}
