#include <algorithm>
#include <iostream>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

const int MAXM = 50;
const int MAXN = 251;
ll dp[MAXM][MAXN] = { 0 };

ll ways(vector<int>& coins, int n) {
  int i, j;
  FOR(i, coins.size()) {
    FOR(j, n+1) {
      dp[i][j] = (i == 0) ? (j % coins[i] == 0) : dp[i-1][j] + ((j - coins[i] >= 0) ? dp[i][j-coins[i]] : 0);
    }
  }
  return dp[coins.size()-1][n];
}

int main() {
  int n, m, i;
  cin >> n >> m;
  vector<int> coins(m);
  FOR(i, m) cin >> coins[i];
  sort(coins.begin(), coins.end());
  cout << ways(coins, n) << endl;
  return 0;
}
