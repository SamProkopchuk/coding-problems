#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

namespace {
struct SuffLex {
  int prevlex, currlex, idx;
  bool operator==(SuffLex a) {
    return prevlex == a.prevlex && currlex == a.currlex;
  }
};

int cmp(SuffLex a, SuffLex b) {
  return a.prevlex == b.prevlex ? (a.currlex < b.currlex)
                                : (a.prevlex < b.prevlex);
}

vector<int> get_suffix_array(const string &s) {
  int i, stp, cnt;

  vector<int> sort_idx(s.length(), 0);
  vector<SuffLex> suff_lexs(s.length());

  for (i = 0; i < s.length(); i++)
    sort_idx[i] = s[i];
  for (stp = 1, cnt = 1; cnt >> 1 < s.length(); stp++, cnt <<= 1) {
    for (i = 0; i < s.length(); i++) {
      suff_lexs[i].prevlex = sort_idx[i];
      suff_lexs[i].currlex = i + cnt < s.length() ? sort_idx[i + cnt] : -1;
      suff_lexs[i].idx = i;
    }
    sort(suff_lexs.begin(), suff_lexs.end(), cmp);
    for (i = 0; i < s.length(); i++)
      sort_idx[suff_lexs[i].idx] = i > 0 && suff_lexs[i] == suff_lexs[i - 1]
                                       ? sort_idx[suff_lexs[i - 1].idx]
                                       : i;
  }

  vector<int> suffix_array(suff_lexs.size(), 0);
  for (i = 0; i < suffix_array.size(); i++)
    suffix_array[i] = suff_lexs[i].idx;

  return suffix_array;
}

// Returns lcp array and inverse suffix array
vector<int> get_lcp_array(const string &s, const vector<int> &suffix_array) {
  const int n = s.size();
  // Inverse of array contains indices of the elements - eg:
  // a     = [2, 1, 3, 0]
  // a_inv = [3, 1, 0, 2]
  vector<int> inverse_suffix_array(n);
  for (int i = 0; i < n; ++i) {
    inverse_suffix_array[suffix_array[i]] = i;
  }

  int k = 0;
  vector<int> lcp_array(n - 1, 0);
  for (int i = 0; i < n; ++i) {
    const int sa_index = inverse_suffix_array[i];
    if (sa_index == n - 1) {
      k = 0;
      continue;
    }
    // j is the index in s of the suffix that's lexicographically ordered right
    // after s[i:]
    int j = suffix_array[sa_index + 1];
    // Update k based on how many characters they have in common:
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
      ++k;
    }
    lcp_array[sa_index] = k;
    if (k > 0) {
      --k;
    }
  }
  return lcp_array;
}

vector<int> get_lookahead_palindrome_lengths(const string &s,
                                             const int special_char_index) {
  string s_prime;
  s_prime.reserve(2 * s.size() + 1);
  for (int i = 0; i < s.size(); i++) {
    s_prime.push_back('|');
    s_prime.push_back(s[i]);
  }
  s_prime.push_back('|');

  vector<int> palindrome_radii(s_prime.size());
  int center = 0;
  int radius = 0;
  while (center < s_prime.size()) {
    while (center - (radius + 1) >= 0 &&
           center + (radius + 1) < s_prime.size() &&
           s_prime[center - (radius + 1)] == s_prime[center + (radius + 1)]) {
      ++radius;
    }
    palindrome_radii[center] = radius;
    int old_center = center;
    int old_radius = radius;
    ++center;
    radius = 0;
    // While whithin the right side of the old palindrome, take advantage of
    // mirror information.
    while (center <= old_center + old_radius) {
      int Mirroredcenter = old_center - (center - old_center);
      int MaxMirroredradius = old_radius - (center - old_center);
      if (palindrome_radii[Mirroredcenter] < MaxMirroredradius) {
        palindrome_radii[center] = palindrome_radii[Mirroredcenter];
        ++center;
      } else if (palindrome_radii[Mirroredcenter] > MaxMirroredradius) {
        palindrome_radii[center] = MaxMirroredradius;
        ++center;
      } else {
        radius = MaxMirroredradius;
        break;
      }
    }
  }
  // Initialize to 1, assuming we consider a single character as a palindrome.
  vector<int> lookahead_palindrome_lengths(s.size(), 1);
  lookahead_palindrome_lengths[special_char_index] = 0;
  for (int i = 1; i < palindrome_radii.size() - 1; ++i) {
    const int s_index = i / 2;
    if (s_index == special_char_index) {
      continue;
    }
    lookahead_palindrome_lengths[s_index - palindrome_radii[i] / 2] =
        max(lookahead_palindrome_lengths[s_index - palindrome_radii[i] / 2],
            palindrome_radii[i]);
  }
  for (int i = 1; i < lookahead_palindrome_lengths.size(); i++) {
    if (i == special_char_index) {
      continue;
    }
    lookahead_palindrome_lengths[i] =
        max(lookahead_palindrome_lengths[i],
            lookahead_palindrome_lengths[i - 1] - 2);
  }
  assert(lookahead_palindrome_lengths[special_char_index] == 0);
  return lookahead_palindrome_lengths;
}

string get_solution(const string &s, const int special_char_index) {
  const vector<int> suffix_array = get_suffix_array(s);
  const vector<int> lcp_array = get_lcp_array(s, suffix_array);
  const vector<int> lookahead_palindrome_lengths =
      get_lookahead_palindrome_lengths(s, special_char_index);

  int running_lcp = 0;
  // Length, -lexicographical suffix index
  pair<int, int> best_score = {0, 0};
  int solution_lcp = 0;

  for (int l = 0; l < suffix_array.size() - 1; ++l) {
    const int i = suffix_array[l];
    const int lcp = lcp_array[l];
    const bool is_second_string = i > special_char_index;
    if (running_lcp != 0) {
      const pair<int, int> score =
          make_pair(2 * running_lcp +
                        (i + running_lcp < lookahead_palindrome_lengths.size()
                             ? lookahead_palindrome_lengths[i + running_lcp]
                             : 0),
                    -l);
      if (score > best_score) {
        best_score = score;
        solution_lcp = running_lcp;
      }
    }
    running_lcp =
        ((suffix_array[l + 1] > special_char_index) != is_second_string)
            ? lcp
            : min(running_lcp, lcp);
  }
  running_lcp = 0;
  for (int l = suffix_array.size() - 2; l >= 0; --l) {
    const int i = suffix_array[l];
    const int lcp = l == 0 ? 0 : lcp_array[l - 1];
    const bool is_second_string = i > special_char_index;
    if (running_lcp != 0) {
      const pair<int, int> score =
          make_pair(2 * running_lcp +
                        (i + running_lcp < lookahead_palindrome_lengths.size()
                             ? lookahead_palindrome_lengths[i + running_lcp]
                             : 0),
                    -l);
      if (score > best_score) {
        best_score = score;
        solution_lcp = running_lcp;
      }
    }
    running_lcp = ((l > 0 && suffix_array[l - 1] > special_char_index) !=
                   is_second_string)
                      ? lcp
                      : min(running_lcp, lcp);
  }

  if (best_score.first != 0) {
    string solution;
    solution.reserve(best_score.first);
    const int i = suffix_array[-best_score.second];
    const string_view common = string_view(s).substr(i, solution_lcp);
    solution.append(common);
    solution.append(string_view(s).substr(i + solution_lcp,
                                          best_score.first - 2 * solution_lcp));
    solution.insert(solution.end(), common.crbegin(), common.crend());
    return solution;
  }
  return "-1";
}
} // namespace

int main() {
  int q;
  string s;
  cin >> q;
  while (q--) {
    s.clear();
    cin >> s;
    const int sa_size = s.size();
    // 'z' is 122, hence 123 (is unique w.r.t. expected input alphabet):
    s.push_back(static_cast<char>(123));
    {
      string sb;
      cin >> sb;
      std::reverse(sb.begin(), sb.end());
      s.append(sb);
    }
    cout << get_solution(s, sa_size) << endl;
  }
  return 0;
}
