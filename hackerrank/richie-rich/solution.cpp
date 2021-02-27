#include <iostream>
#include <string>

using namespace std;

int highest_value_palindrome(string &s, size_t k) {
  int i, l, d;
  l = s.length();
  for (d = 0, i = 0; i < l / 2; ++i)
    if (s[i] != s[l - 1 - i]) ++d;
  if (k < d) return -1;
  for (i = 0; i < l / 2; ++i) {
    if (s[i] != s[l - 1 - i]) {
      (s[i] > s[l - 1 - i]) ? (s[l - 1 - i] = s[i]) : (s[i] = s[l - 1 - i]);
      if (k == d || s[i] == '9')
        --k, --d;
      else if (k >= 2)
        s[i] = '9', s[l - 1 - i] = '9', k -= 2, --d;
    } else if (k > d && k >= 2 && s[i] != '9') {
      s[i] = '9';
      s[l - 1 - i] = '9';
      k -= 2;
    }
  }
  if (l % 2 && k > 0) s[l / 2] = '9';
  return 0;
}

int main() {
  int n, k;
  string s;
  cin >> n >> k >> s;
  if (highest_value_palindrome(s, k) != -1)
    cout << s << endl;
  else
    cout << -1 << endl;
  return 0;
}
