#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORG(x, fm, to) for (x = (fm); x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

int solve(vector<int> &arr) {
  sort(arr.begin(), arr.end(), greater<int>());
  int res = INT_MAX, minel = *arr.rbegin(), shift;
  FOR(shift, 3) {
    int curres = 0;
    FORR(x, arr) {
      int d =  x + shift - minel;
      curres += d / 5 + (d % 5) / 2 + (d % 5) % 2;
    }
    res = min(res, curres);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n, i, tmp;
    cin >> n;
    vector<int> arr(n);
    FOR(i, n) cin >> arr[i];
    cout << solve(arr) << endl;
  }
  return 0;
}
