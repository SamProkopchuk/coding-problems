#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

bool is_receive_notification(const vector<int> &trailing, int &spent) {
  return (trailing.size() % 2)
             ? (spent >= 2 * trailing[trailing.size() / 2])
             : (spent >= (trailing[(trailing.size() - 1) / 2] +
                          trailing[trailing.size() / 2]));
}

void remove_key_from_vector(vector<int> &v, const int &key) {
  int l = 0, h = v.size() - 1, m;
  while (v[m = (l + h) / 2] != key) {
    if (v[m] < key)
      l = m + 1;
    else
      h = m;
  }
  v.erase(v.begin() + m);
}

int main() {
  int expidentures[200] = {0};
  int n, d, spent, notifs = 0;
  cin >> n >> d;
  queue<int> trailing;
  vector<int> ordered_trailing;
  for (int i = 0; i < n; ++i) {
    cin >> spent;
    if (trailing.size() == d) {
      if (is_receive_notification(ordered_trailing, spent)) ++notifs;
      int torm = trailing.front();
      trailing.pop();
      remove_key_from_vector(ordered_trailing, torm);
    }
    ordered_trailing.insert(
        upper_bound(ordered_trailing.begin(), ordered_trailing.end(), spent),
        spent);
    trailing.push(spent);
  }
  cout << notifs << endl;
  return 0;
}
