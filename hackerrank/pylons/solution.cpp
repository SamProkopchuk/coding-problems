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
  int last = -1;
  int num_plants = 0;
  for (int i = 0; i < n; ++i) {
    if (last == -1 || i - last >= k) {
      for (int j = min(i + k - 1, n - 1); j >= max(0, i - k + 1); --j) {
        if (b[j]) {
          last = j;
          ++num_plants;
          break;
        }
      }
      if (last == -1 || i - last >= k) {
        return -1;
      }
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
