#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

const size_t RANGE_SIZE = 4001;

int num[RANGE_SIZE];
int numleq[RANGE_SIZE];
ll sumleq[RANGE_SIZE];

int main() {
  ios_base::sync_with_stdio(false);
  int i, n, q, temp;
  cin >> n;
  FOR(i, n) {
    cin >> temp;
    ++num[temp + 2000];
  }
  FOR(i, RANGE_SIZE) {
    sumleq[i] = ((i) ? sumleq[i - 1] : 0) + num[i] * (i - 2000);
    numleq[i] = ((i) ? numleq[i - 1] : 0) + num[i];
  }
  ll off = 0;
  cin >> q;
  while (q--) {
    cin >> temp;
    off += temp;
    ll ans;
    if (off < -2000 || off > 2000)
      ans = abs(sumleq[4000] + numleq[4000] * off);
    else if (off < 0) {
      ans = abs(sumleq[2000] + numleq[2000] * off) +
            abs((sumleq[2000 - off] - sumleq[2000]) +
                (numleq[2000 - off] - numleq[2000]) * off) +
            abs((sumleq[4000] - sumleq[2000 - off]) +
                (numleq[4000] - numleq[2000 - off]) * off);
    } else {
      ans = abs(sumleq[2000 - off] + numleq[2000 - off] * off) +
            abs((sumleq[2000] - sumleq[2000 - off]) +
                (numleq[2000] - numleq[2000 - off]) * off) +
            abs((sumleq[4000] - sumleq[2000]) +
                (numleq[4000] - numleq[2000]) * off);
    }
    cout << ans << endl;
  }
  return 0;
}
