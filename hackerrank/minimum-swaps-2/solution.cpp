#include <iostream>
#include <vector>

#define FOR(x, to) for (x = 0; x < (to); ++x)

using namespace std;

int main() {
  int i, n, swaps;
  cin >> n;
  vector<int> vec(n);
  FOR(i, n) cin >> vec[i];
  swaps = 0;
  FOR(i, n) {
    while (vec[i] != i + 1) {
      swap(vec[i], vec[vec[i] - 1]);
      ++swaps;
    }
  }
  cout << swaps << endl;
  return 0;
}
