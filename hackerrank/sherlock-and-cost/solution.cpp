#include <algorithm>
#include <iostream>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

int main() {
  int t, i, n, pbest1, pbestm, cbest1, cbestm;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> B(n);
    FOR(i, n) cin >> B[i];
    pbest1 = pbestm = 0;
    for (i=1; i<n; ++i) {
      cbest1 = pbestm + abs(B[i-1] - 1);
      cbestm = max(pbest1 + abs(B[i] - 1), pbestm + abs(B[i] - B[i-1]));
      pbest1 = cbest1;
      pbestm = cbestm;
    }
    cout << max(cbest1, cbestm) << endl;
  }
}
