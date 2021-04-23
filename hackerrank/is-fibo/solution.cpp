#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

ll MAXQ = 1e10;

unordered_set<ll> getFib() {
  unordered_set<ll> res = {0};
  ll a = 0, b = 1, t;
  while (b <= MAXQ) {
    res.insert(b);
    t = b;
    b = a + b;
    a = t;
  }
  return res;
}

int main() {
  ll t, n;
  unordered_set<ll> fib = getFib();
  cin >> t;
  while (t--) {
    cin >> n;
    cout << (fib.count(n) ? "IsFibo" : "IsNotFibo") << endl;
  }
  return 0;
}
