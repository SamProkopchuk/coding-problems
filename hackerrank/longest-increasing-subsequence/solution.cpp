#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int n, i, x;
  map<int, int> lis2MinTail = {{1, INT_MAX}};
  map<int, int> minTail2Lis = {{-INT_MAX, 1}};
  std::map<int, int>::iterator it;
  cin >> n;
  FOR(i, n) {
    cin >> x;
    if (x < lis2MinTail[1]) {
      minTail2Lis.erase(-lis2MinTail[1]);
      lis2MinTail[1] = x;
      minTail2Lis[-x] = 1;
    } else if ((it = minTail2Lis.upper_bound(-x)) != minTail2Lis.end()) {
      int lis = it->second + 1;
      if (!lis2MinTail.count(lis)) {
        lis2MinTail[lis] = x;
        minTail2Lis[-x] = lis;
      } else if (x < lis2MinTail[lis]) {
        minTail2Lis.erase(-lis2MinTail[lis]);
        lis2MinTail[lis] = x;
        minTail2Lis[-x] = lis;
      }
    }
  }
  cout << lis2MinTail.rbegin()->first << endl;
  return 0;
}
