#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

int main() {
  int t, n, i, x, cursum, maxsubarr, maxsubseq, largest;
  cin >> t;
  while (t--) {
    cin >> n;
    cursum = maxsubarr = maxsubseq = 0;
    largest = INT_MIN;
    FOR(i, n) {
      cin >> x;
      largest = max(largest, x);
      cursum += x;
      maxsubseq = max(maxsubseq, maxsubseq + x);
      maxsubarr = max(maxsubarr, cursum);
      cursum = max(cursum, 0);
    }
    if (largest < 0) maxsubseq = maxsubarr = largest;
    cout << maxsubarr << " " << maxsubseq << endl;
  }
  return 0;
}
