#include <iostream>
#include <vector>

using namespace std;

int main() {
  int test_cases, t, n, i, swaps;
  cin >> test_cases;

  for (t = 0; t < test_cases; t++) {
    cin >> n;
    vector<int> nums(n, 0);
    swaps = 0;
    for (i = 0; i < n; i++) cin >> nums[i];
    for (i = 0; i < n; i++)
      for (; nums[i] != i + 1; swaps++) swap(nums[i], nums[nums[i] - 1]);
    cout << ((swaps % 2 == 0) ? "YES" : "NO") << endl;
  }
  return 0;
}
