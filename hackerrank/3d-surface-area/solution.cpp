#include <cmath>
#include <iostream>

using namespace std;

int main() {
  int h, w, sa, v;
  cin >> h >> w;
  sa = 2 * h * w;
  int matrix[h][w];
  for (int r = 0; r < h; r++) {
    for (int c = 0; c < w; c++) {
      cin >> v, matrix[r][c] = v;
      sa += r ? abs(v - matrix[r - 1][c]) : v;
      sa += c ? abs(v - matrix[r][c - 1]) : v;
      if (r == h - 1) sa += v;
      if (c == w - 1) sa += v;
    }
  }
  cout << sa << endl;
  return 0;
}
