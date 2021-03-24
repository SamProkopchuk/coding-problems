#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

const int MAXN = 100;
const int MAXM = 100;
char grid[MAXN][MAXM];
int n, m;

bool isValid(int r, int c) { return 0 <= r && r < n && 0 <= c && c < m; }

int dfs(int r, int c) {
  if (grid[r][c] == '*') return 0;
  grid[r][c] = 'X';
  int options = 0, res = -1;
  for (int dr = -1; dr < 2; ++dr) {
    for (int dc = -1; dc < 2; ++dc) {
      if ((dr == 0) ^ (dc == 0) && isValid(r + dr, c + dc) &&
          grid[r + dr][c + dc] != 'X') {
        ++options;
        res = max(res, dfs(r + dr, c + dc));
      }
    }
  }
  if (res == -1) return res;
  return (options > 1) ? res + 1 : res;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  string row;
  cin >> t;
  while (t--) {
    int k, i, j;
    cin >> n >> m;
    FOR(i, n) {
      cin >> row;
      FOR(j, m) { grid[i][j] = row[j]; }
    }
    cin >> k;
    int ans;
    FOR(i, n) {
      FOR(j, m) {
        if (grid[i][j] == 'M') ans = dfs(i, j);
      }
    }
    cout << ((k == ans) ? "Impressed" : "Oops!") << endl;
  }
  return 0;
}
