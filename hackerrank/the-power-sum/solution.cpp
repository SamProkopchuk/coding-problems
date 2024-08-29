#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

constexpr int MAXX = 1001;

int dp[MAXX];

void precompute(int n, int i, int last) {
  for (int next = last + 1; next < MAXX; ++next) {
    const int x = pow(next, n);
    const int j = i + x;
    if (j > MAXX) {
      break;
    } else {
      ++dp[j];
      precompute(n, j, next);
    }
  }
}

int main() {
  int x, n;
  cin >> x >> n;
  fill(dp, dp + 1001, 0);
  precompute(n, 0, 0);
  cout << dp[x] << endl;
}
