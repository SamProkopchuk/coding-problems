#include <iostream>
#include <unordered_map>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

int main() {
  int n, r, i, x;
  ll res;
  cin >> n >> r;
  vector<int> nums(n);
  FOR(i, n) cin >> nums[i];
  unordered_map<int, int> seen;
  unordered_map<int, ll> jks;
  res = 0;
  for (i = n - 1; i >= 0; --i) {
    x = nums[i];
    if (jks.count(r * x)) res += jks[r * x];
    if (seen.count(r * x))
      jks[x] = jks.count(x) ? jks[x] + seen[r * x] : seen[r * x];
    seen[x] = seen.count(x) ? seen[x] + 1 : 1;
  }
  cout << res << endl;
  return 0;
}
