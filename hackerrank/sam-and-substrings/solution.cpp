#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

const int MOD = 1e9 + 7;

int main() {
  string s;
  cin >> s;
  ll fact = 1, ans = 0;
  for (int i = s.length() - 1; i >= 0; --i) {
    ans = (ans + (s[i] - '0') * (i + 1) * fact) % MOD;
    fact = (fact * 10 + 1) % MOD;
  }
  cout << ans << endl;
  return 0;
}
