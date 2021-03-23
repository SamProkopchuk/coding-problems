#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int n, i, j;
  cin >> n;
  string s;
  cin >> s;
  map<char, int> cc = {{'G', 0}, {'C', 0}, {'A', 0}, {'T', 0}};
  FORR(c, s) { cc[c] += 1; }
  if (cc['G'] == n / 4 && cc['C'] == n / 4 && cc['A'] == n / 4 &&
      cc['T'] == n / 4)
    cout << 0 << endl;
  else {
    int best = INT_MAX;
    i = 0;
    FOR(j, n) {
      cc[s[j]] -= 1;
      if (cc['G'] <= n / 4 && cc['C'] <= n / 4 && cc['A'] <= n / 4 &&
          cc['T'] <= n / 4) {
        for (; i < j; ++i) {
          if (cc[s[i]] == n / 4) break;
          cc[s[i]] += 1;
        }
        best = min(best, j - i + 1);
      }
    }
    cout << best << endl;
  }
  return 0;
}
