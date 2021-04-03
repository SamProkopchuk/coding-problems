#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORG(x, fm, to) for (x = (fm); x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

bool visited[1 << 20] = {false};

int hashDisks(vector<int> &disks) {
  int i, res = 0;
  FOR(i, disks.size()) { res += (disks[i] - 1) << (i << 1); }
  return res;
}

bool canMoveDisk(vector<int> &disks, int i, int rod) {
  int j;
  FOR(j, i) {
    if (disks[j] == rod || disks[j] == disks[i]) return false;
  }
  return true;
}

int solve(vector<int> &disks) {
  queue<pair<vector<int>, int>> q;
  q.push({disks, 0});
  visited[hashDisks(disks)] = true;
  vector<int> state;
  int moves, i, rod;
  while (q.size()) {
    state = q.front().first;
    moves = q.front().second;
    q.pop();
    if (*max_element(state.begin(), state.end()) == 1) return moves;
    FOR(i, state.size()) {
      FORG(rod, 1, 5) {
        if (state[i] != rod && canMoveDisk(state, i, rod)) {
          int temp = state[i];
          state[i] = rod;
          if (!visited[hashDisks(state)]) {
            visited[hashDisks(state)] = true;
            q.push({state, moves + 1});
          }
          state[i] = temp;
        }
      }
    }
  }
  return moves;
}

int main() {
  int n, i;
  cin >> n;
  vector<int> disks(n);
  FOR(i, n) cin >> disks[i];
  cout << solve(disks) << endl;
  return 0;
}
