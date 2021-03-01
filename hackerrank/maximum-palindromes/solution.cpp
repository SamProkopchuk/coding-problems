#include <iostream>
#include <string>
#include <vector>

using namespace std;

const size_t ALPHABET_SIZE = 26;
const long long MOD = 1e9 + 7;
const size_t MAX_INPUT = 1e5;

int mod(long long a) { return (a % MOD + MOD) % MOD; }

long long binpow(long long a, long long b) {
  long long res = 1;
  while (b) {
    if (b & 1)
      res = mod(res * a);
    a = mod(a * a);
    b >>= 1;
  }
  return res;
}

vector<vector<int>> getCumCharCount(const string &s) {
  vector<vector<int>> res(s.length());
  vector<int> cur(ALPHABET_SIZE);
  for (int i = 0; i < s.length(); ++i) {
    ++cur[s[i] - 'a'];
    res[i] = cur;
  }
  return res;
}

vector<long long> getFactorials(size_t max_factorial) {
  vector<long long> res(max_factorial);
  res[0] = 1;
  for (int i = 1; i < max_factorial; ++i) res[i] = mod(res[i - 1] * i);
  return res;
}

vector<long long> getInverseFactorials(vector<long long> factorials) {
  vector<long long> res(factorials.size());
  for (int i = 0; i < factorials.size(); ++i)
    res[i] = binpow(factorials[i], MOD-2);
  return res;
}

int getNumOfMaxLenPalindromes(const vector<vector<int>> &char_count,
                              const int &l, const int &r,
                              const vector<long long> &factorials,
                              const vector<long long> &inverse_factorials) {
  int i, ichars, dups_in_range, center_pieces;
  long long res;
  vector<int> char_dups(ALPHABET_SIZE);
  dups_in_range = 0, center_pieces = 0;
  for (i = 0; i < ALPHABET_SIZE; ++i) {
    ichars = char_count[r][i] - ((l == 0) ? 0 : char_count[l - 1][i]);
    char_dups[i] = ichars / 2;
    dups_in_range += char_dups[i];
    if (ichars % 2) ++center_pieces;
  }
  res = factorials[dups_in_range];
  for (i = 0; i < ALPHABET_SIZE; ++i)
    res = mod(res * inverse_factorials[char_dups[i]]);
  return mod(res * ((center_pieces == 0) ? 1 : center_pieces));
}

int main() {
  int q, i, l, r;
  string s;
  vector<long long> factorials = getFactorials(MAX_INPUT / 2 + 1);
  vector<long long> inverse_factorials = getInverseFactorials(factorials);
  cin >> s >> q;
  vector<vector<int>> char_count = getCumCharCount(s);
  for (i = 0; i < q; ++i) {
    cin >> l >> r;
    --l, --r;
    cout << getNumOfMaxLenPalindromes(char_count, l, r, factorials,
                                      inverse_factorials)
         << endl;
  }
  return 0;
}
