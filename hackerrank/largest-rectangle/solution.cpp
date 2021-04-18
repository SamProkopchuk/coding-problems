#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int n, i, j;
  cin >> n;
  vector<ll> H(n + 1, 0);
  FOR(i, n) { cin >> H[i]; }
  ll ans = 0;
  stack<ll> stk;
  FOR(i, n+1) {
    while (!stk.empty() && H[j = stk.top()] > H[i]) {
      stk.pop();
      ans = max(ans, H[j] * (stk.empty() ? i : (i - stk.top() - 1)));
    }
    stk.push(i);
  }
  cout << ans << endl;
  return 0;
}
