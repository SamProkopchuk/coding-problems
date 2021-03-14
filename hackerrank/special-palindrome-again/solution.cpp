#include <cstring>
#include <iostream>
#include <string>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

int main() {
  int n, i;
  string s;
  ll res;
  int c[3];

  cin >> n >> s;

  res = 0;
  memset(c, -1, sizeof(c));
  FOR(i, n) {
    if (i && s[i] != s[i - 1]) c[0] = c[1], c[1] = c[2], c[2] = i - 1;
    res += i - c[2];
    if (c[1] != -1 && c[2] - c[1] == 1 && c[1] - c[0] >= i - c[2] &&
        s[c[1]] == s[i])
      ++res;
  }
  cout << res << endl;
  return 0;
}
