#include <bits/stdc++.h>

typedef signed long long ll;
typedef unsigned long long ull;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

ll solve(ll y, ll x) {
  ll m = (y % x + x) % x;
  return (y - m < 0 || x - m < m) ? (y + x - m) : y - m;
}

int main() {
  int t;
  ll a, b, x, y;
  cin >> t;
  while (t--) {
    cin >> a >> b >> x;
    cout << solve(pow(a, b), x) << endl;
  }
  return 0;
}
