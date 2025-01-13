#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

namespace {

template <typename eT> void visualize_vector(const vector<eT> vec) {
  for (const eT &elem : vec) {
    cout << elem << " ";
  }
  cout << endl;
}

// Adapted from https://cp-algorithms.com/string/suffix-array.html
vector<int> get_suffix_array(string s, const int alphabet_size = 256) {
  s += '$';
  cout << "s: " << s << endl;
  // p[i] = index of the ith suffix in the sorted order.
  // c[i] = equivalence class of the ith suffix.
  // cnt[i] = count of equivalence class i.
  const int n = s.size();
  vector<int> p(n), c(n), cnt(max(n, alphabet_size), 0);
  for_each(s.cbegin(), s.cend(), [&](const char &ch) { ++cnt[ch]; });
  // There are only alphabet_size equivalence classid on the first iteration.
  inclusive_scan(cnt.cbegin(), cnt.cbegin() + alphabet_size, cnt.begin());
  // Counting sort.
  for (int i = 0; i < n; ++i) {
    p[--cnt[s[i]]] = i;
  }
  c[p[0]] = 0;
  int classid = 0;
  for (int i = 1; i < n; ++i) {
    if (s[p[i]] != s[p[i - 1]]) {
      ++classid;
    }
    c[p[i]] = classid;
  }
  vector<int> pn(n), cn(n);
  for (int shift = 1; shift < n; shift <<= 1) {
    // Set pn[i] to be the index of the 2^hth-sized previous suffix
    for (int i = 0; i < n; ++i) {
      pn[i] = (p[i] - shift + n) % n;
    }
    fill(cnt.begin(), cnt.begin() + classid, 0);
    for_each(pn.cbegin(), pn.cend(), [&](const int &x) { ++cnt[c[x]]; });
    const int num_classes = classid + 1;
    inclusive_scan(cnt.cbegin(), cnt.cbegin() + num_classes, cnt.begin());
    for_each(p.crbegin(), p.crend(),
             [&](const int &x) { pn[--cnt[c[x]]] = x; });
    cn[p[0]] = 0;
    classid = 0;
    for (int i = 1; i < n; i++) {
      pair<int, int> cur = {c[p[i]], c[(p[i] + shift) % n]};
      pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + shift) % n]};
      if (cur != prev)
        ++classid;
      cn[p[i]] = classid;
    }
    c.swap(cn);
  }
  p.erase(p.begin());
  return p;
}

} // namespace

int main() {
  string s;
  cin >> s;
  visualize_vector(get_suffix_array(s));
}
