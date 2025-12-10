#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct point {
  long x, y;
};

bool intersects(point r_min, point r_max, point p1, point p2) {
  if (p1.x == p2.x) {
    long edge_x = p1.x;
    long edge_y_min = std::min(p1.y, p2.y);
    long edge_y_max = std::max(p1.y, p2.y);

    if (edge_x > r_min.x && edge_x < r_max.x) {
      if (std::max(r_min.y, edge_y_min) < std::min(r_max.y, edge_y_max)) {
        return true;
      }
    }
  } else {
    long edge_y = p1.y;
    long edge_x_min = std::min(p1.x, p2.x);
    long edge_x_max = std::max(p1.x, p2.x);

    if (edge_y > r_min.y && edge_y < r_max.y) {
      if (std::max(r_min.x, edge_x_min) < std::min(r_max.x, edge_x_max)) {
        return true;
      }
    }
  }
  return false;
}

bool is_interior(point r_min, point r_max, const std::vector<point> &poly) {
  double test_x = (r_min.x + r_max.x) / 2.0;
  double test_y = (r_min.y + r_max.y) / 2.0;

  bool inside = false;
  size_t n = poly.size();

  for (size_t i = 0; i < n; ++i) {
    point p1 = poly[i];
    point p2 = poly[(i + 1) % n];

    if (p1.y == p2.y)
      continue;

    if (((p1.y > test_y) != (p2.y > test_y))) {

      // Calculate intersection X
      // For a vertical line (p1.x == p2.x), this simplifies to p1.x
      double intersect_x =
          (double)(p2.x - p1.x) * (test_y - p1.y) / (double)(p2.y - p1.y) +
          p1.x;

      if (test_x < intersect_x) {
        inside = !inside;
      }
    }
  }
  return inside;
}

int main() {
  std::vector<point> pos;
  long x, y;
  char p;

  while (std::cin >> x >> p >> y) {
    pos.push_back({x, y});
  }

  size_t n = pos.size();
  long long max_area = 0;

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {

      long tl_x = std::min(pos[i].x, pos[j].x);
      long tl_y = std::min(pos[i].y, pos[j].y);
      long br_x = std::max(pos[i].x, pos[j].x);
      long br_y = std::max(pos[i].y, pos[j].y);

      long long width = (br_x - tl_x + 1);
      long long height = (br_y - tl_y + 1);
      long long area = width * height;

      if (area <= max_area)
        continue;

      bool flag = false;
      for (size_t k = 0; k < n; ++k) {
        point p1 = pos[k];
        point p2 = pos[(k + 1) % n];
        if (intersects({tl_x, tl_y}, {br_x, br_y}, p1, p2)) {
          flag = true;
          break;
        }
      }
      if (flag)
        continue;

      if (is_interior({tl_x, tl_y}, {br_x, br_y}, pos)) {
        max_area = std::max(area, max_area);
      }
    }
  }

  std::cout << "max area = " << max_area << "\n";
  return 0;
}
