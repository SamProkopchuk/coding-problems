#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORG(x, fm, to) for (x = (fm); x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

const int MAXN = 37;
const ll MOD = 1e10 + 7;
ll dp[MAXN];

ll solve(int n) {
  if (dp[n] == -1) {
    int i;
    dp[n] = 0;
    FORG(i, 1, 4) {
      if (n - i >= 0) dp[n] = (dp[n] + solve(n - i)) % MOD;
    }
  }
  return dp[n];
}

int main() {
  ios_base::sync_with_stdio(false);
  fill(begin(dp), end(dp), -1);
  dp[0] = 1;
  int s;
  cin >> s;
  while (s--) {
    int n;
    cin >> n;
    cout << solve(n) << endl;
  }
  return 0;
}
