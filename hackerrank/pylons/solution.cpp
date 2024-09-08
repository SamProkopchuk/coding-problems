#include <bitset>
#include <cassert>
#include <deque>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

namespace {

constexpr int MAX_N = 100000;

int get_solution(const bitset<MAX_N> &b, int n, int k) {
  int num_plants = 0;
  for (int i = 0; i < n;) {
    bool found = false;
    for (int j = min(i + k - 1, n - 1); j >= max(0, i - k + 1); --j) {
      if (b[j]) {
        i = j + k;
        ++num_plants;
        found = true;
        break;
      }
    }
    if (!found) {
      return -1;
    }
  }
  return num_plants;
}

} // namespace

int main() {
  int n;
  int k;
  cin >> n >> k;
  bitset<MAX_N> b;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    b[i] = x;
  }
  cout << get_solution(b, n, k) << endl;
}
