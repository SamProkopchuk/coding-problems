#include <iostream>
#include <string>
#include <vector>

using namespace std;

ostream &operator<<(ostream &os, vector<int> v) {
  os << '|';
  for (const int &i : v) {
    os << i << '|';
  }
  return os;
}

vector<int> manacher(const string &s) {
  string s_prime;
  s_prime.reserve(2 * s.size() + 1);
  for (int i = 0; i < s.size(); i++) {
    s_prime.push_back('|');
    s_prime.push_back(s[i]);
  }
  s_prime.push_back('|');
  cout << "s_prime: " << s_prime << endl;

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
  // Remove the '|' characters from the palindrome_radii vector.
  vector<int> odds;
  vector<int> evens;
  odds.reserve(palindrome_radii.size() / 2);
  evens.reserve(palindrome_radii.size() / 2 - 1);
  evens.push_back(0);
  for (int i = 1; i < palindrome_radii.size() - 1; ++i) {
    if (i % 2 == 0) {
      evens.push_back(palindrome_radii[i]);
    } else {
      odds.push_back(palindrome_radii[i]);
    }
  }
  // Initialize to 1, assuming we consider a single character as a palindrome.
  vector<int> lookahead_palindrome_lengths(s.size(), 1);
  for (int i = 0; i < odds.size(); ++i) {
    lookahead_palindrome_lengths[i - odds[i] / 2] =
        max(lookahead_palindrome_lengths[i - odds[i] / 2], odds[i]);
  }
  for (int i = 0; i < evens.size(); ++i) {
    lookahead_palindrome_lengths[i - evens[i] / 2] =
        max(lookahead_palindrome_lengths[i - evens[i] / 2], evens[i]);
  }
  for (int i = 1; i < lookahead_palindrome_lengths.size(); ++i) {
    lookahead_palindrome_lengths[i] = max(lookahead_palindrome_lengths[i],
                                          lookahead_palindrome_lengths[i - 1] - 2);
  }
  cout << "temp: " << lookahead_palindrome_lengths << endl;
  cout << "odds:    " << odds << endl;
  cout << "evens:   " << evens << endl;
  return palindrome_radii;
}

int main() {
  string s;
  cin >> s;
  vector<int> p = manacher(s);
  cout << "----------------" << endl;
  cout << "p: " << p << endl;
}
