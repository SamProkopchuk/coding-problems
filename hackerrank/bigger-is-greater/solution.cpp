#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int tests, idx, swapidx;
  string s;
  cin >> tests;
  for (int test = 0; test < tests; test++) {
    s.clear();
    cin >> s;
    for (idx = s.length() - 1; idx > -1; idx--) {
      if (idx != s.length() - 1 && s[idx] < s[idx + 1]) {
        swap(s[idx], *min_element(next(s.begin(), idx + 1), s.end(),
                                  [&s, &idx](char a, char b) {
                                    return (a > s[idx]) && (a < b);
                                  }));
        sort(next(s.begin(), idx + 1), s.end());
        cout << s << endl;
        break;
      }
    }
    if (idx == -1) cout << "no answer" << endl;
  }
  return 0;
}
