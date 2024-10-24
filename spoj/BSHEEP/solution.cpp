#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

namespace {

constexpr int MAX_N = 100000;
using Point = pair<int, int>;

double Distance(const Point &a, const Point &b) {
  const double x_diff = b.first - a.first;
  const double y_diff = b.second - a.second;
  return sqrt(x_diff * x_diff + y_diff * y_diff);
}

// Returns the cross product of vectors ab and ac.
// Positive if counter-clockwise, negative if clockwise, and zero if collinear.
constexpr double CrossProduct(const Point &a, const Point &b, const Point &c) {
  return (b.first - a.first) * (c.second - a.second) -
         (b.second - a.second) * (c.first - a.first);
}

void Solve(array<pair<int, Point>, MAX_N> &points_orig, const int n_orig) {
  array<pair<int, Point>, MAX_N> points;
  array<pair<int, Point>, MAX_N> hull;
  if (n_orig == 1) {
    cout << 0.0 << endl;
    cout << 1 << endl;
    return;
  }
  stable_sort(points_orig.begin(), points_orig.begin() + n_orig,
              [](const auto &a, const auto &b) {
                return a.second.second < b.second.second ||
                       (a.second.second == b.second.second &&
                        a.second.first < b.second.first);
              });
  // Remove duplicate points:
  int n = 0;
  for (int i = 0; i < n_orig; ++i) {
    if (i == 0 || points_orig[i].second != points_orig[i - 1].second) {
      points[n] = points_orig[i];
      ++n;
    }
  }
  int num_hull_points = 0;
  for (int i = 0; i < n; ++i) {
    const Point &point = points[i].second;
    while (num_hull_points >= 2 &&
           CrossProduct(hull[num_hull_points - 2].second,
                        hull[num_hull_points - 1].second, point) <= 0) {
      --num_hull_points;
    }
    hull[num_hull_points] = points[i];
    ++num_hull_points;
  }
  --num_hull_points;
  const int num_upper_hull_points = num_hull_points;
  for (int i = n - 1; i >= 0; --i) {
    const Point &point = points[i].second;
    while (num_hull_points - num_upper_hull_points >= 2 &&
           CrossProduct(hull[num_hull_points - 2].second,
                        hull[num_hull_points - 1].second, point) <= 0) {
      --num_hull_points;
    }
    hull[num_hull_points] = points[i];
    ++num_hull_points;
  }
  --num_hull_points;
  // Compute perimeter:
  double perimeter = Distance(hull[0].second, hull[num_hull_points - 1].second);
  for (int i = 0; i < num_hull_points - 1; ++i) {
    perimeter += Distance(hull[i].second, hull[i + 1].second);
  }
  cout << perimeter << endl;
  for (int i = 0; i < num_hull_points; ++i) {
    cout << hull[i].first + 1;
    if (i != num_hull_points - 1) {
      cout << ' ';
    }
  }
  cout << endl;
}

} // namespace

int main() {
  int t;
  array<pair<int, Point>, MAX_N> points;
  cout << fixed << setprecision(2);
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
      auto &p = points[i];
      p.first = i;
      cin >> p.second.first >> p.second.second;
    }
    Solve(points, n);
    cout << endl;
  }
  return 0;
}
