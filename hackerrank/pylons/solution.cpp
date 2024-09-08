#include <bitset>
#include <cassert>
#include <deque>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

namespace {

constexpr int MAX_N = 100000;

int solve(const bitset<MAX_N> &b, int n, int k) {
  // leftmost / rightmost
  vector<int> lm_plant(n);
  vector<int> rm_plant(n);
  deque<int> dq;
  for (int i = 0; i < n; ++i) {
    if (b[i]) {
      dq.push_back(i);
    }
    while (!dq.empty() && i - dq.front() >= k) {
      dq.pop_front();
    }
    lm_plant[i] = dq.empty() ? -1 : dq.front();
  }
  dq.clear();
  int last = -1;
  for (int i = n - 1; i >= 0; --i) {
    if (lm_plant[i] != -1) {
      last = lm_plant[i];
    } else if (last != -1 && last - i < k) {
      assert(last > i);
      lm_plant[i] = last;
    }
    if (b[i]) {
      dq.push_back(i);
    }
    while (!dq.empty() && dq.front() - i >= k) {
      dq.pop_front();
    }
    rm_plant[i] = dq.empty() ? -1 : dq.front();
    if (rm_plant[i] == -1 && lm_plant[i] == -1) {
      return -1;
    }
  }
  last = -1;
  for (int i = 0; i < n; ++i) {
    if (rm_plant[i] != -1) {
      last = rm_plant[i];
    } else if (last != -1 && i - last < k) {
      assert(i > last);
      rm_plant[i] = last;
    }
  }

  vector<int> rm_solution(n, 0);
  last = -1;
  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      rm_solution[i] = rm_solution[i - 1];
    }
    if (last == -1 || abs(i - last) >= k) {
      last = rm_plant[i];
      ++rm_solution[i];
    }
  }
  vector<int> lm_solution(n, 0);
  last = -1;
  for (int i = n - 1; i >= 0; --i) {
    if (i < n - 1) {
      lm_solution[i] = lm_solution[i + 1];
    }
    if (last == -1 || abs(i - last) >= k) {
      last = lm_plant[i];
      ++lm_solution[i];
    }
  }
  int best_solution = numeric_limits<int>::max();
  for (int i = -1; i < n; ++i) {
    int solution = (i < n - 1) ? lm_solution[i + 1] : 0;
    if (i >= 0) {
      solution += rm_solution[i];
    }
    best_solution = min(best_solution, solution);
  }
  return best_solution;
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
  cout << solve(b, n, k) << endl;
}
