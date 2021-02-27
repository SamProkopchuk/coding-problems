#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct RC {
  size_t r, c;
};

bool valid_idx(int h, int v) { return (0 <= v && v < h); }

int main() {
  int n, m, i, j, dr, dc, cur_region, max_region;
  RC rc;
  queue<RC> q;

  cin >> n >> m;
  int matrix[n][m];
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j) cin >> matrix[i][j];
  max_region = 0;
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j)
      if (matrix[i][j]) {
        matrix[i][j] = 0;
        rc.r = i, rc.c = j;
        q.push(rc);
        for (cur_region=0; q.size(); ++cur_region) {
          rc = q.front();
          q.pop();
          for (dr = -1; dr < 2; ++dr)
            for (dc = -1; dc < 2; ++dc)
              if ((dr || dc) && valid_idx(n, rc.r + dr) &&
                  valid_idx(m, rc.c + dc) && matrix[rc.r + dr][rc.c + dc]) {
                rc.r += dr, rc.c += dc;
                matrix[rc.r][rc.c] = 0;
                q.push(rc);
              }
        }
        max_region = max(max_region, cur_region);
      }
  cout << max_region << endl;
  return 0;
}
