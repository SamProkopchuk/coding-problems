#include <array>
#include <cstdint>
#include <iostream>
#include <optional>
#include <set>
#include <utility>

using namespace std;

namespace {

constexpr int kMaxN = 1000;
constexpr double kEps = 1e-9;

constexpr bool DoubleEqual(double a, double b) { return abs(a - b) < kEps; }

class Rng {
public:
  Rng() : s(290797) {}

  int Get() {
    s = (s * s) % 50515093;
    return s % 500;
  }

private:
  uint64_t s;
};

struct Point {
  double x, y;
  constexpr bool operator<(const Point &p) const {
    return (DoubleEqual(x, p.x) && !DoubleEqual(y, p.y) && y < p.y) || x < p.x;
  }
  // Cross product.
  constexpr double operator*(const Point &p) const { return x * p.y - y * p.x; }
  constexpr Point operator*(const double d) const { return {x * d, y * d}; }
  constexpr Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }
  constexpr Point operator-(const double d) const { return {x - d, y - d}; }
  constexpr Point operator+(const Point &p) const { return {x + p.x, y + p.y}; }
  constexpr bool ApproxEqual(const Point &p) const {
    return DoubleEqual(x, p.x) && DoubleEqual(y, p.y);
  }
};

using Segment = pair<Point, Point>;

// https://stackoverflow.com/a/565282/10166393
constexpr optional<Point> GetIntersection(const Segment &s1,
                                          const Segment &s2) {
  const Point d1 = {s1.second.x - s1.first.x, s1.second.y - s1.first.y};
  const Point d2 = {s2.second.x - s2.first.x, s2.second.y - s2.first.y};
  const double cross = d1 * d2;
  if (DoubleEqual(cross, 0)) {
    return nullopt;
  }
  const Point diff = s2.first - s1.first;

  const double t1 = (diff * d2) / cross;
  const double t2 = (diff * d1) / cross;

  if (DoubleEqual(t1, 0) || DoubleEqual(t1, 1) || DoubleEqual(t2, 0) ||
      DoubleEqual(t2, 1) || t1 < 0 || t1 > 1 || t2 < 0 || t2 > 1) {
    return nullopt;
  }
  return s1.first + d1 * t1;
}

// Count number of intersections n has with previous segments.
int GetNumIntersections(const array<Segment, kMaxN> &segments, const int n,
                        set<Point> &intersections) {
  int num_intersections = 0;
  for (int i = 0; i < n; ++i) {
    if (auto intersection = GetIntersection(segments[i], segments[n])) {
      const Point &p = *intersection;
      const Point ptemp = p - kEps;
      auto it = intersections.lower_bound(ptemp);
      if (it == intersections.end() || !it->ApproxEqual(ptemp)) {
        intersections.insert(p);
        ++num_intersections;
      }
    }
  }
  return num_intersections;
}

} // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  array<Segment, kMaxN> segments;
  Rng rng;
  int num_intersections = 0;
  set<Point> intersections;
  for (int i = 0; i < n; ++i) {
    segments[i].first.x = rng.Get();
    segments[i].first.y = rng.Get();
    segments[i].second.x = rng.Get();
    segments[i].second.y = rng.Get();
    if (i > 0) {
      num_intersections += GetNumIntersections(segments, i, intersections);
    }
  }
  cout << num_intersections << endl;
}
