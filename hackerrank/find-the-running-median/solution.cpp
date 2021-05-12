#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cout << fixed << setprecision(1);
  int i, n, x;
  cin >> n;
  vector<int> nums;
  FOR(i, n) {
    float m;
    cin >> x;
    nums.insert(lower_bound(nums.begin(), nums.end(), x), x);
    m = (i % 2 == 0) ? (float)nums[nums.size() / 2]
                     : ((float)nums[nums.size() / 2 - 1] +
                        (float)nums[nums.size() / 2]) / 2;
    cout << m << endl;
  }
  return 0;
}
