/*
 * This solution doesn't use recursion.
 * Recursion would likely allow far cleaner code.
 */

#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <cstring>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

const size_t MAXN = 1000;
bool dp[MAXN][MAXN];

bool isAbbr(string& a, string& b) {
  int i, j;
  stack<pair<int, int>> last;
  i = j = 0;
  while (j < b.length()) {
    while (i < a.length() && a[i] != b[j]) {
      if (a[i] <= 90) {
        if (last.empty()) return false;
        i = last.top().first;
        j = last.top().second;
        last.pop();
        dp[i][j] = false;
        break;
      } else if (a[i] - 32 == b[j] && dp[i][j])
        last.push({i, j});
      ++i;
    }
    if (i >= a.length()) {
      if (last.empty()) return false;
      i = last.top().first;
      j = last.top().second;
      last.pop();
      dp[i][j] = false;
    }
    ++j, ++i;
  }
  for (;i < a.length(); ++i)
    if (a[i] <= 90) return false;
  return true;
}

int main() {
  int test, tests;
  cin >> tests;
  string a, b;
  FOR(test, tests) {
    memset(dp, true, MAXN * MAXN * sizeof(bool));
    cin >> a >> b;
    cout << ((isAbbr(a, b)) ? "YES" : "NO") << endl;
  }
  return 0;
}
