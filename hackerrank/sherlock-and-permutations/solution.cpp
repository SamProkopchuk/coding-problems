#include <bits/stdc++.h>

typedef signed long long ll;
typedef unsigned long long ull;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

const ll MOD = 1e9 + 7;
const size_t MAXQ = 2001;

ll factorials[MAXQ];
ll inverseModulos[MAXQ];
ll inverseFactorials[MAXQ];

ll mod(ll i, ll m) { return (i % m + m) % m; }

void preCalculateFactorials() {
  factorials[0] = 1;
  for (int i = 1; i < MAXQ; ++i) {
    factorials[i] = mod(factorials[i - 1] * i, MOD);
  }
}

void preCalculateInverseModulos() {
  inverseModulos[0] = -1, inverseModulos[1] = 1;
  for (int i = 2; i < MAXQ; ++i) {
    inverseModulos[i] = mod(-MOD / i * inverseModulos[mod(MOD, i)], MOD);
  }
}

void preCalculateInverseFactorials() {
  preCalculateInverseModulos();
  inverseFactorials[0] = 1, inverseFactorials[1] = inverseModulos[1];
  for (int i = 2; i < MAXQ; ++i) {
    inverseFactorials[i] =
        mod(inverseFactorials[i - 1] * inverseModulos[i], MOD);
  }
}

ll solve(int n, int m) {
  ll ans;
  m--;
  ans = mod(factorials[n + m] * inverseFactorials[n], MOD);
  ans = mod(ans * inverseFactorials[m], MOD);
  return ans;
}

int main() {
  int t, n, m;
  // Precalculate in O(MAXQ)
  preCalculateFactorials();
  preCalculateInverseFactorials();
  cin >> t;
  while (t--) {
    // Solve each test case in O(1)
    cin >> n >> m;
    cout << solve(n, m) << endl;
  }
  return 0;
}
