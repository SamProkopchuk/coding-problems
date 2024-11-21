#include <array>
#include <cstdint>
#include <iostream>
#include <limits>
#include <set>
#include <utility>

namespace {

using namespace std;

constexpr double kNull = numeric_limits<double>::quiet_NaN();
static_assert(kNull != kNull);

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
  static constexpr Point NullPoint() { return Point{kNull, kNull}; }
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
  constexpr bool IsNull() const { return x != x; }
};

using Segment = pair<Point, Point>;

// https://stackoverflow.com/a/565282/10166393
constexpr Point GetIntersection(const Segment &s1, const Segment &s2) {
  const Point d1 = {s1.second.x - s1.first.x, s1.second.y - s1.first.y};
  const Point d2 = {s2.second.x - s2.first.x, s2.second.y - s2.first.y};
  const double cross = d1 * d2;
  if (DoubleEqual(cross, 0)) {
    return Point::NullPoint();
  }
  const Point diff = s2.first - s1.first;

  const double t1 = (diff * d2) / cross;
  const double t2 = (diff * d1) / cross;

  if (DoubleEqual(t1, 0) || DoubleEqual(t1, 1) || DoubleEqual(t2, 0) ||
      DoubleEqual(t2, 1) || t1 < 0 || t1 > 1 || t2 < 0 || t2 > 1) {
    return Point::NullPoint();
  }
  return s1.first + d1 * t1;
}

// Add points of intersection of segments[0..n-1] with segment n
void ComputeIntersections(const array<Segment, kMaxN> &segments, const int n,
                          set<Point> &intersections) {
  for (int i = 0; i < n; ++i) {
    const Point intersection = GetIntersection(segments[i], segments[n]);
    if (!intersection.IsNull()) {
      auto it = intersections.lower_bound(intersection);
      if (it == intersections.end() || !it->ApproxEqual(intersection)) {
        intersections.emplace(std::move(intersection));
      }
    }
  }
}

} // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  array<Segment, kMaxN> segments;
  Rng rng;
  set<Point> intersections;
  for (int i = 0; i < n; ++i) {
    segments[i].first.x = rng.Get();
    segments[i].first.y = rng.Get();
    segments[i].second.x = rng.Get();
    segments[i].second.y = rng.Get();
    ComputeIntersections(segments, i, intersections);
  }
  cout << intersections.size() << endl;
}
