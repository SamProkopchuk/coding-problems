#include <iostream>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

int main() {
  int t, n, i, mprice;
  ll profit;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> prices(n);
    FOR(i, n) cin >> prices[i];
    mprice = profit = 0;
    for (i = n - 1; i >= 0; --i) {
      if (prices[i] > mprice)
        mprice = prices[i];
      else
        profit += mprice - prices[i];
    }
    cout << profit << endl;
  }
  return 0;
}
