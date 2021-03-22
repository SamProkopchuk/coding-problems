#include <climits>
#include <iostream>
#include <set>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

int main() {
  int n, i;
  ll price, minloss;
  cin >> n;
  set<ll> seen;
  set<ll>::iterator it;
  minloss = LLONG_MAX;
  FOR(i, n) {
    cin >> price;
    if (seen.size()) {
      if ((it = seen.lower_bound(price)) != seen.end())
        minloss = min(minloss, *it - price);
    }
    seen.insert(price);
  }
  cout << minloss << endl;
  return 0;
}
