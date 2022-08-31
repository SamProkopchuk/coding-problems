#include <bits/stdc++.h>

typedef signed long long ll;
typedef unsigned long long ull;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

const ll MOD = 1e9 + 7;

int main() {
  int q, i;
  ll a, b, ans;
  string as, bs;
  cin >> q;
  while (q--) {
    cin >> as >> bs;
    a = b = 0;
    FOR(i, as.size()) { a = (a * 10 + (as[i] - '0')) % MOD; }
    FOR(i, bs.size()) { b = (b * 10 + (bs[i] - '0')) % (MOD - 1); }
    ans = 1;
    while (b > 0) {
      if (b % 2 == 1) {
        ans = ans * a % MOD;
      }
      a = a * a % MOD;
      b /= 2;
    }
    cout << ans << endl;
  }
  return 0;
}
