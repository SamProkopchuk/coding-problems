#include <algorithm>
#include <iostream>
#include <vector>

#define FOR(x, to) for (x = 0; x < (to); ++x)

using namespace std;

int main() {
  int t, tests, i, n, res;
  cin >> tests;
  FOR(t, tests) {
    res = 0;
    cin >> n;
    vector<int> q(n);
    vector<int> b(n + 1, 0);
    FOR(i, n) cin >> q[i];
    i = 0;
    while (i < n - 1) {
      if (q[i] > q[i + 1]) {
        if (b[q[i]] == 2) {
          res = -1;
          break;
        }
        swap(q[i], q[i + 1]), ++res, ++b[q[i + 1]];
        if (i) --i;
      } else
        ++i;
    }
    if (res == -1)
      cout << "Too chaotic" << endl;
    else
      cout << res << endl;
  }
  return 0;
}
