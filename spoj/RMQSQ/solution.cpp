#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

const int MAXN = 1e5;
const int LOG = 17;
int m[MAXN][LOG];

int getMin(int l, int r) {
  int k = 31 - __builtin_clz(r - l + 1);
  return min(m[l][k], m[r - (1 << k) + 1][k]);
}

int main() {
  int n, i, k;
  cin >> n;
  FOR(i, n) { cin >> m[i][0]; }
  for (k = 1; k < LOG; ++k) {
    FOR(i, n + 1 - (1 << k)) {
      m[i][k] = min(m[i][k - 1], m[i + (1 << (k - 1))][k - 1]);
    }
  }
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << getMin(l, r) << endl;
  }
  return 0;
}