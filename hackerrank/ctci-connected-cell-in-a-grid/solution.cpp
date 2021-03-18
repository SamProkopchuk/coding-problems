#include <iostream>
#include <cstring>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

const int MAXN = 10;
int grid[MAXN][MAXN];
int n, m;

int regionSize(int r, int c) {
  if (!grid[r][c])
    return 0;
  --grid[r][c];
  int res, dr, dc, r_, c_;
  res = 1;
  for (dr=-1; dr<2; ++dr)
    for (dc=-1; dc<2; ++dc) {
      r_ = r + dr;
      c_ = c + dc;
      if (0 <= r_ && r_ < n && 0 <= c_ && c_ < m && grid[r_][c_])
        res += regionSize(r_, c_);
    }
  return res;
}

int main() {
  int r, c, res;
  res = 0;
  cin >> n >> m;
  FOR(r, n)
    FOR(c, m)
      cin >> grid[r][c];
  FOR(r, n)
    FOR(c, m)
      if (grid[r][c])
        res = max(res, regionSize(r, c));
  cout << res << endl;
  return 0;
}
