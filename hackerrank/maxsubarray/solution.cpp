#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

int main() {
  int t, n, i, maxsubarr, maxsubseq, largest;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> arr(n);
    vector<int> cumsum(n);
    vector<int> revmaxcumsum(n);
    maxsubseq = 0;
    largest = INT_MIN;
    FOR(i, n) {
      cin >> arr[i];
      maxsubseq = max(maxsubseq, maxsubseq + arr[i]);
      largest = max(largest, arr[i]);
    }
    if (largest < 0) maxsubseq = largest;
    cumsum[0] = arr[0];
    for (i = 1; i < n; ++i) cumsum[i] = cumsum[i - 1] + arr[i];
    revmaxcumsum[n - 1] = cumsum[n - 1];
    for (i = n - 2; i >= 0; --i)
      revmaxcumsum[i] = max(revmaxcumsum[i + 1], cumsum[i]);
    maxsubarr = revmaxcumsum[0];
    FOR(i, n - 1) {
      maxsubarr = max(maxsubarr, revmaxcumsum[i + 1] - cumsum[i]);
    }
    cout << maxsubarr << " " << maxsubseq << endl;
  }
  return 0;
}
