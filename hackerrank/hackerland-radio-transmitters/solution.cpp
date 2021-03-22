#include <algorithm>
#include <iostream>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 200;

int main() {
  int n, k, i;
  cin >> n >> k;
  vector<int> houses(n);
  FOR(i, n) cin >> houses[i];
  sort(houses.begin(), houses.end());
  int start = houses[0], mid = 0, res = 1;
  FOR(i, n - 1) {
    if (mid == 0 && houses[i + 1] - start > k) mid = houses[i];
    if (mid && houses[i + 1] - mid > k) {
      start = houses[i + 1];
      mid = 0;
      ++res;
    }
  }
  cout << res << endl;
  return 0;
}
