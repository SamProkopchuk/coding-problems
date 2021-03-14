#include <algorithm>
#include <iostream>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

const int MAXN = 1e5;
int mem[MAXN];

ll solve(vector<int>& arry, int l, int r) {
  ll swaps = 0;
  if (r - l > 1) {
    int m = (l + r) / 2;
    swaps += solve(arry, l, m);
    swaps += solve(arry, m, r);
    int i, j, k;
    for (k = l, i = l, j = m; i < m && j < r; ++k) {
      if (arry[i] <= arry[j])
        mem[k] = arry[i], ++i;
      else
        mem[k] = arry[j], swaps += m - i, ++j;
    }
    while (i < m) mem[k] = arry[i], ++i, ++k;
    while (j < r) mem[k] = arry[j], ++j, ++k;
    for (i = l, k = 0; i < r; ++i) arry[i] = mem[i];
  }
  return swaps;
}

int main() {
  int t, tests, n, i;
  cin >> tests;
  FOR(t, tests) {
    cin >> n;
    vector<int> arry(n);
    FOR(i, n) cin >> arry[i];
    cout << solve(arry, 0, n) << endl;
  }
  return 0;
}
