#include <algorithm>
#include <iostream>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)

using namespace std;

struct q {
  ll i, d;
};

int cmp(q &a, q &b) { return a.i == b.i ? a.d < b.d : a.i < b.i; }

int main() {
  int n, m, i;
  ll cur, max_;
  cin >> n >> m;
  vector<q> qs(2 * m);
  FOR(i, m) {
    cin >> qs[i].i >> qs[m + i].i;
    ++qs[m + i].i;
    cin >> qs[i].d;
    qs[m + i].d = -qs[i].d;
  }
  sort(qs.begin(), qs.end(), cmp);
  cur = max_ = 0;
  FOR(i, 2 * m) {
    cur += qs[i].d;
    max_ = max(cur, max_);
  }
  cout << max_ << endl;
  return 0;
}
