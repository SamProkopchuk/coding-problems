#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORG(x, fm, to) for (x = (fm); x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

const int SIZE = 100;
int board[SIZE];
int D[SIZE];
int DP[SIZE];

int solve(int i, int depth) {
  i = board[i];
  if (depth > D[i]) return 1e9;
  D[i] = depth;
  if (DP[i] == -1) {
    int roll;
    DP[i] = 1e9;
    FORG(roll, 1, 7) {
      if (i + roll < SIZE) DP[i] = min(DP[i], solve(i + roll, depth + 1) + 1);
    }
  }
  return DP[i];
}

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n, m, i, k, v;
    fill(begin(D), end(D), INT_MAX);
    fill(begin(DP), end(DP), -1);
    DP[99] = 0;
    FOR(i, 100) { board[i] = i; }
    cin >> n;
    FOR(i, n) {
      cin >> k >> v;
      board[k - 1] = v - 1;
    }
    cin >> m;
    FOR(i, m) {
      cin >> k >> v;
      board[k - 1] = v - 1;
    }
    cout << (solve(0, 0) > 99 ? -1 : solve(0, 0)) << endl;
  }
  return 0;
}
