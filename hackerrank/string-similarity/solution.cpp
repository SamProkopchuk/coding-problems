#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (int x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto &x : arr)
#define LSBIT(x) ((x) & -(x))

using namespace std;

vector<int> getZ(string &s) {
  vector<int> Z(s.length(), 0);
  Z[0] = s.length();
  int l = 0, r = 0;
  for (int i = 1; i < s.length(); ++i) {
    if (i > r) {
      l = r = i;
      while (r < s.length() && s[r] == s[r - l]) ++r;
      Z[i] = r - l;
      --r;
    } else if (Z[i - l] <= r - i) {
      Z[i] = Z[i - l];
    } else {
      l = i;
      while (r < s.length() && s[r] == s[r - l]) ++r;
      Z[i] = r - l;
      --r;
    }
  }
  return Z;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    vector<int> Z = getZ(s);
    ll ans = 0;
    FORR(x, Z) { ans += x; }
    cout << ans << endl;
  }
  return 0;
}
