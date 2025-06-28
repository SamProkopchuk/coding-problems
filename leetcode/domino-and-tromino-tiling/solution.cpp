#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>

using namespace std;

constexpr uint64_t kMod = 1e9 + 7;

struct State {
  uint64_t a;
  uint64_t b;
  uint64_t c;
};

class Solution {
public:
  static int numTilings(int n) {
    uint64_t curr = 1;
    array<State, 3> ways{};
    ways[0].a = 1;
    for (int i = 0; i < n; ++i) {
      ways[0].a %= kMod;
      ways[0].b %= kMod;
      ways[0].c %= kMod;
      ways[2].a += ways[0].a;
      ways[1].a += ways[0].a;
      ways[1].b += ways[0].a;
      ways[1].c += ways[0].a;
      ways[2].a += ways[0].b;
      ways[1].c += ways[0].b;
      ways[2].a += ways[0].c;
      ways[1].b += ways[0].c;
      copy(next(ways.begin()), ways.end(), ways.begin());
      ways.back() = State{};
    }
    return ways[0].a % kMod;
  }
};

int main() {
  int n;
  cin >> n;
  cout << Solution::numTilings(n) << endl;
  return 0;
}
