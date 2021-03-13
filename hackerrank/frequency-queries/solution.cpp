#include <iostream>
#include <unordered_map>
#include <vector>

typedef signed long long ll;

#define FOR(x, to) for (x = 0; x < (to); ++x)
#define FORR(x, arr) for (auto& x : arr)

using namespace std;

struct query {
  int q, x;
};

int main() {
  int nq, i;
  cin >> nq;
  vector<query> qs(nq);
  FOR(i, nq) cin >> qs[i].q >> qs[i].x;
  unordered_map<int, int> m;
  unordered_map<int, int> freq;
  FORR(q, qs) {
    switch (q.q) {
      case 1:
        if (m.count(q.x) && freq.count(m[q.x]) && freq[m[q.x]]) --freq[m[q.x]];
        m[q.x] = m.count(q.x) ? m[q.x] + 1 : 1;
        if (freq.count(m[q.x]))
          ++freq[m[q.x]];
        else
          freq[m[q.x]] = 1;
        break;
      case 2:
        if (m.count(q.x) && m[q.x]) {
          if (freq.count(m[q.x]) && freq[m[q.x]]) --freq[m[q.x]];
          --m[q.x];
          if (freq.count(m[q.x]))
            ++freq[m[q.x]];
          else
            freq[m[q.x]] = 1;
        }
        break;
      case 3:
        cout << ((freq.count(q.x) && freq[q.x]) ? 1 : 0) << endl;
        break;
    }
  }
  return 0;
}
