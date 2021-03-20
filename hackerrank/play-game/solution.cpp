#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

const int MAXN = 1e5;
ll dp[MAXN];

ll bestScore(vector<int>& arr, int idx, bool maximizer) {
  if (idx >= arr.size()) return 0;
  int i;
  if (maximizer) {
    if (dp[idx] == -1) {
      int subsum = 0;
      for (i = 0; idx + i < arr.size() && i < 3; ++i) {
        subsum += arr[idx + i];
        dp[idx] = max(dp[idx], subsum + bestScore(arr, idx + i + 1, false));
      }
    }
    return dp[idx];
  } else {
    ll res = LLONG_MAX;
    FOR(i, 3) { res = min(res, bestScore(arr, idx + i + 1, true)); }
    return res;
  }
}

int main() {
  int t, n, i;
  cin >> t;
  while (t--) {
    fill(begin(dp), end(dp), -1);
    cin >> n;
    vector<int> arr(n);
    FOR(i, n) cin >> arr[i];
    cout << bestScore(arr, 0, true) << endl;
  }
  return 0;
}
