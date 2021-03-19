#include <iostream>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

const int MAXN = 2001;
int dp[MAXN];

int leastDiff(vector<int>& arr, int k) {
  if (dp[k] == -1) {
    int min_ = k;
    FORR(x, arr) {
      if (k - x >= 0) min_ = min(min_, leastDiff(arr, k - x));
    }
    dp[k] = min_;
  }
  return dp[k];
}

int main() {
  int t, n, k, i;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    vector<int> arr(n);
    fill(begin(dp), end(dp), -1);
    dp[0] = 0;
    FOR(i, n) cin >> arr[i];
    cout << k - leastDiff(arr, k) << endl;
  }
  return 0;
}
