#include <iostream>
#include <vector>

using namespace std;

bool is_sorted(const vector<int>& v) {
  for (int i = 0; i < v.size(); ++i)
    if (i != 0 && v[i - 1] > v[i]) return false;
  return true;
}

bool is_in_order(const int& a, const int& b, const int& c) {
  return a < b && b < c;
}

bool is_sorted_by_swap(const vector<int>& v, const int& l, const int& r) {
  if (v.size() == 2) return v[l] > v[r];
  return ((l == 0 && v[r] < v[1]) || is_in_order(v[l - 1], v[r], v[l + 1])) &&
         ((r == v.size() - 1 && v[r - 1] < v[l]) ||
          is_in_order(v[r - 1], v[l], v[r + 1]));
}

int is_sortable_by_swap(const vector<int>& v, int& l, int& r) {
  l = -1, r = -1;
  for (int i = 0; i < v.size(); i++) {
    if (i != 0 && v[i - 1] > v[i]) {
      if (l == -1) {
        l = i - 1;
      } else if (r == -1) {
        r = i;
      } else {
        return false;
      }
    }
  }

  if (l == -1 && r == -1) return false;
  if (l != -1 && r != -1) return is_sorted_by_swap(v, l, r);
  r = v.size() - 1;
  return is_sorted_by_swap(v, l, r);
}

bool is_sortable_by_segment_reverse(const vector<int>& v, int& l, int& r) {
  int descending_runs = 0;
  bool descending_run = false;
  l = -1;
  r = -1;
  for (int i = 0; i < v.size(); ++i) {
    if (i != 0 && v[i - 1] > v[i]) {
      if (!descending_run) {
        l = i - 1;
        if (++descending_runs > 1) return false;
        descending_run = true;
      }
    } else if (descending_run) {
      r = i - 1;
      descending_run = false;
    }
  }

  if (l == -1 && r == -1) return false;
  if (l != -1 && r != -1) return v[l] < v[r + 1] && (l == 0 || v[l - 1] < v[r]);
  r = v.size() - 1;
  return l == 0 || v[l - 1] < v[r];
}

int main() {
  int n, l, r;

  cin >> n;
  vector<int> nums(n, 0);

  for (int i = 0; i < n; ++i) cin >> nums[i];

  if (is_sorted(nums)) {
    cout << "yes" << endl;
  } else if (is_sortable_by_swap(nums, l, r)) {
    cout << "yes" << endl;
    cout << "swap " << (l + 1) << " " << (r + 1) << endl;
  } else if (is_sortable_by_segment_reverse(nums, l, r)) {
    cout << "yes" << endl;
    cout << ((r == l + 1) ? "swap " : "reverse ") << (l + 1) << " " << (r + 1)
         << endl;
  } else {
    cout << "no" << endl;
  }

  return 0;
}
