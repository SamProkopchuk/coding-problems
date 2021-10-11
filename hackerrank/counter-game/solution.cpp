#include <bits/stdc++.h>

typedef signed long long ll;
typedef unsigned long long ull;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

#define isPowerOf2(x) (((x - 1) & x) == 0)

int main() {
  int t;
  cin >> t;
  while (t--) {
    ull n, lbit, p;
    p = 0;
    lbit = ~(((ull)-1) << 1 >> 1);
    cin >> n;
    if (n == 1) {
      p = 1;
    } else {
      while (n != 1) {
        while (!(lbit & n)) {
          lbit >>= 1;
        }
        if (lbit == n) {
          n >>= 1;
        } else {
          n -= lbit;
        }
        ++p;
      }
    }
    cout << ((p % 2) ? "Louise" : "Richard") << endl;
  }
  return 0;
}