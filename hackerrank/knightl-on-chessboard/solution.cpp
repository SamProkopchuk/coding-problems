#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Knight {
  int r, u;
};

struct Point {
  int r, c;
};

bool is_valid_point(Point &p, size_t &n) {
  return (0 <= p.r && p.r < n && 0 <= p.c && p.c < n);
}

int calc_least_moves(int board[25][25], Knight &knight, size_t &n) {
  queue<Point> q;
  Point next;
  next.r = 0;
  next.c = 0;
  q.push(next);
  while (!q.empty()) {
    Point p = q.front();
    q.pop();
    for (int coefr = -1; coefr < 2; coefr += 2)
      for (int coefu = -1; coefu < 2; coefu += 2)
        for (int i = 0; i < 2; ++i) {
          next.r = p.r + coefr * knight.r;
          next.c = p.c + coefu * knight.u;
          if (next.r == n - 1 && next.c == n - 1) return board[p.r][p.c] + 1;
          if (is_valid_point(next, n) && board[next.r][next.c] == 0) {
            board[next.r][next.c] = board[p.r][p.c] + 1;
            q.push(next);
          }
          swap(knight.r, knight.u);
        }
  }
  return -1;
}

int main() {
  size_t n;
  cin >> n;

  Knight knight;
  for (int r = 1; r < n; ++r) {
    for (int u = 1; u < n; ++u) {
      int board[25][25] = {};
      knight.r = r;
      knight.u = u;
      cout << calc_least_moves(board, knight, n) << " ";
    }
    cout << endl;
  }
  return 0;
}
