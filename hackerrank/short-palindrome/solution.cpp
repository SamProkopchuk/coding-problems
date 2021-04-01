#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORG(x, fm, to) for (x = (fm); x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

const int MOD = 1e9 + 7;
const int A = 26;

ll shortPalindromes(string &s) {
  int i, j;
  ll c1[26] = {0};
  ll c2[26][26] = {0};
  ll c3[26] = {0};
  ll res = 0;
  FORR(c, s) {
    i = c - 'a';
    res = (res + c3[i]) % MOD;
    FOR(j, 26) { c3[j] = (c3[j] + c2[j][i]) % MOD; }
    FOR(j, 26) { c2[j][i] = (c2[j][i] + c1[j]) % MOD; }
    ++c1[i];
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  string s;
  cin >> s;
  cout << shortPalindromes(s) << endl;
  return 0;
}
