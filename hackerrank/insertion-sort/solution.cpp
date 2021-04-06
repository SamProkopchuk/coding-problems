#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

const int MAXQ = 1e7;

struct BIT {
  vector<int> bit;
  int added;

  BIT() {
    bit = vector<int>(MAXQ + 1);
    reset();
  }

  void reset() {
    fill(bit.begin(), bit.end(), 0);
    added = 0;
  }

  int numGreater(int x) {
    int nLEQ = 0;
    for (; x > 0; x -= LSBIT(x)) {
      nLEQ += bit[x];
    }
    return added - nLEQ;
  }

  void add(int x) {
    for (; x < bit.size(); x += LSBIT(x)) {
      ++bit[x];
    }
    ++added;
  }
};

int main() {
  int t;
  BIT bit;
  cin >> t;
  while (t--) {
    bit.reset();
    int n, temp;
    cin >> n;
    ll ans = 0;
    while (n--) {
      cin >> temp;
      ans += bit.numGreater(temp);
      bit.add(temp);
    }
    cout << ans << endl;
  }
}
