#include <bits/stdc++.h>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORG(x, fm, to) for (x = (fm); x < (to); ++x)
#define FORREV(x, to) for (x = (to)-1; x >= 0; --x)
#define FORR(x, arr) for (auto &x : arr)

using namespace std;

const int MAXN = 1e5;
int arr[MAXN];
int idxs[MAXN];

bool comp(int &a, int &b) { return arr[a] > arr[b]; }

int main() {
  int g, n, i;
  cin >> g;
  while (g--) {
    cin >> n;
    FOR(i, n) { cin >> arr[i]; }
    FOR(i, n) { idxs[i] = i; }
    sort(begin(idxs), begin(idxs) + n, comp);
    int minIdx = INT_MAX;
    int rounds = 0;
    FOR(i, n) {
      if (idxs[i] < minIdx) minIdx = idxs[i], ++rounds;
    }
    cout << ((rounds % 2 == 1) ? "BOB" : "ANDY") << endl;
  }
  return 0;
}
