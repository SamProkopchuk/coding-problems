#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> get_lcp_array(const string &s, const vector<int> &suffix_array) {
  const int n = s.size();
  // Inverse of array contains indices of the elements - eg:
  // a     = [2, 1, 3, 0]
  // a_inv = [3, 1, 0, 2]
  vector<int> inverse_suffix_array(n);
  for (int i = 0; i < n; ++i) {
    inverse_suffix_array[suffix_array[i]] = i;
  }

  int k = 0;
  vector<int> lcp_array(n - 1, 0);
  for (int i = 0; i < n; ++i) {
    const int sa_index = inverse_suffix_array[i];
    if (sa_index == n - 1) {
      k = 0;
      continue;
    }
    // j is the index in s of the suffix that's lexicographically ordered right
    // after s[i:]
    int j = suffix_array[sa_index + 1];
    // Update k based on how many characters they have in common:
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
      ++k;
    }
    lcp_array[sa_index] = k;
    if (k > 0) {
      --k;
    }
  }
  return lcp_array;
}

ostream& operator <<(ostream&os, vector<int> v) {
  os << '|';
  for (const int &i : v) {
    os << i << '|';
  }
  return os;
}

int main() {
  const string s = "bananasna";
  const vector<int> suffix_array = {8, 1, 3, 5, 0, 7, 2, 4, 6};
  cout << "string: " << s << endl;
  cout << "suffix_array: " << suffix_array;
  cout << endl;
  cout << "lcp_array: " << get_lcp_array(s, suffix_array) << endl;
  return 0;
}
