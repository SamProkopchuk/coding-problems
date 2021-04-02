#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORG(x, fm, to) for (x = (fm); x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

struct DSetElem {
  int p, n;
};

int getParent(vector<DSetElem> &disjoint, int i) {
  int p = i;
  while (p != disjoint[p].p) p = disjoint[p].p;
  while (disjoint[i].p != i) {
    int t = disjoint[i].p;
    disjoint[i].p = p;
    i = t;
  }
  return p;
}

void disjointUnion(vector<DSetElem> &disjoint, int i, int j) {
  if (getParent(disjoint, i) != getParent(disjoint, j)) {
    int in, jn;
    in = disjoint[getParent(disjoint, i)].n;
    jn = disjoint[getParent(disjoint, j)].n;
    disjoint[getParent(disjoint, i)].p = getParent(disjoint, j);
    disjoint[getParent(disjoint, i)].n = in + jn;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int n, p, i, a, b;
  cin >> n >> p;
  vector<DSetElem> disjoint(n);
  FOR(i, n) {
    disjoint[i].p = i;
    disjoint[i].n = 1;
  }
  FOR(i, p) {
    cin >> a >> b;
    disjointUnion(disjoint, a, b);
  }
  ll ans = 0;
  FOR(i, n) {
    if (disjoint[i].p == i) ans += (n - disjoint[i].n) * disjoint[i].n;
  }
  ans /= 2;
  cout << ans << endl;
  return 0;
}
