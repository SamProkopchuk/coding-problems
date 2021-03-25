#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    string a, b, c;
    cin >> a >> b;
    int al = a.length(), bl = b.length(), i = 0, j = 0, i_, j_;
    while (i < al && j < bl) {
      if (a[i] < b[j])
        c.push_back(a[i]), ++i;
      else if (b[j] < a[i])
        c.push_back(b[j]), ++j;
      else {
        i_ = i, j_ = j;
        while (i_ < al && j_ < bl && a[i_] == b[j_]) ++i_, ++j_;
        if (i_ == al || (j_ != bl && b[j_] < a[i_])) {
          j_ = j;
          while (j < bl && b[j] == b[j_]) c.push_back(b[j]), ++j;
        } else {
          i_ = i;
          while (i < al && a[i] == a[i_]) c.push_back(a[i]), ++i;
        }
      }
    }
    while (i < al) c.push_back(a[i]), ++i;
    while (j < bl) c.push_back(b[j]), ++j;
    cout << c << endl;
  }
}
