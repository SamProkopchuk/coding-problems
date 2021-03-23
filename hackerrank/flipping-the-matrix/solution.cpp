#include <iostream>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

const int MAXN = 128;
int matrix[2 * MAXN][2 * MAXN];

int main() {
  ios_base::sync_with_stdio(false);
  int q, n, i, j, b, m;
  cin >> q;
  while (q--) {
    cin >> n;
    FOR(i, 2 * n) {
      FOR(j, 2 * n) { cin >> matrix[i][j]; }
    }
    m = 0;
    FOR(i, n) {
      FOR(j, n) {
        b = matrix[i][j];
        b = max(b, matrix[2 * n - 1 - i][j]);
        b = max(b, matrix[i][2 * n - 1 - j]);
        b = max(b, matrix[2 * n - 1 - i][2 * n - 1 - j]);
        m += b;
      }
    }
    cout << m << endl;
  }
  return 0;
}
