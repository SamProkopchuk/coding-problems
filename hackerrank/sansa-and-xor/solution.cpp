#include <bits/stdc++.h>

typedef signed long long ll;
typedef unsigned long long ull;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, i, x, ans;
    ans = 0;
    cin >> n;
    FOR(i, n) {
      cin >> x;
      if (n % 2 && (i + 1) % 2) ans ^= x;
    }
    cout << ans << endl;
  }
  return 0;
}
