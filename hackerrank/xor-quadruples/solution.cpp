#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

int main() {
  int i, j;
  vector<int> A(4);
  FOR(i, 4) { cin >> A[i]; }
  sort(A.begin(), A.end());
  vector<ll> cdxor(4096, 0);
  ll cdcomb = 0;
  for (i = 1; i < A[2] + 1; ++i)
    for (j = i; j < A[3] + 1; ++j) ++cdcomb, ++cdxor[i ^ j];
  ll ans = 0;
  for (j = 1; j < A[1] + 1; ++j) {
    for (i = 1; i < min(j, A[0]) + 1; ++i) ans += cdcomb - cdxor[i ^ j];
    for (i = j; i < A[3] + 1; ++i) --cdxor[j ^ i], --cdcomb;
  }
  cout << ans << endl;
  return 0;
}
