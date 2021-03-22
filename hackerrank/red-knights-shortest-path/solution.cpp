#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 200;
pair<int, int> board[MAXN][MAXN];
pair<int, int> order[6] = {{-2, -1}, {-2, 1}, {0, 2}, {2, 1}, {2, -1}, {0, -2}};
int n;

bool isValidIdx(int i) { return 0 <= i && i < n; }

void query(queue<pair<int, int>>& q, int inir, int inic, int dr, int dc) {
  int r = inir + dr, c = inic + dc;
  if (isValidIdx(r) && isValidIdx(c) && board[r][c].first == -1) {
    q.push({r, c});
    board[r][c].first = inir;
    board[r][c].second = inic;
  }
}

bool solve(int inir, int inic, int dstr, int dstc) {
  int dr, dc;
  queue<pair<int, int>> q;
  q.push({inir, inic});
  while (q.size()) {
    inir = q.front().first;
    inic = q.front().second;
    q.pop();
    FORR(move, order) {
      dr = move.first;
      dc = move.second;
      query(q, inir, inic, dr, dc);
      if (inir + dr == dstr && inic + dc == dstc) return true;
    }
  }
  return false;
}

int main() {
  int inir, inic, dstr, dstc, dr, dc, r, c;
  map<pair<int, int>, string> deltaToMoveString = {
      {{-2, -1}, "UL"}, {{-2, 1}, "UR"}, {{0, -2}, "L"},
      {{0, 2}, "R"},    {{2, -1}, "LL"}, {{2, 1}, "LR"}};
  cin >> n;
  FOR(r, n) {
    FOR(c, n) { board[r][c] = {-1, -1}; }
  }
  cin >> inir >> inic >> dstr >> dstc;
  if (solve(inir, inic, dstr, dstc)) {
    stack<pair<int, int>> deltas;
    int rA, cA, rB, cB;
    rB = dstr;
    cB = dstc;
    while (rB != inir || cB != inic) {
      rA = board[rB][cB].first;
      cA = board[rB][cB].second;
      deltas.push({rB - rA, cB - cA});
      rB = rA, cB = cA;
    }
    cout << deltas.size() << endl;
    while (deltas.size()) {
      cout << deltaToMoveString[deltas.top()] << " ", deltas.pop();
    }
    cout << endl;
    board[dstr];
  } else
    cout << "Impossible" << endl;
  return 0;
}
