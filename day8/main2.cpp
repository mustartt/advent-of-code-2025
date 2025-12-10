#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

struct vec3 {
  int x, y, z;
};

std::ostream &operator<<(std::ostream &os, const vec3 &v) {
  return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

double dist(const vec3 &a, const vec3 &b) {
  double dx = b.x - a.x;
  double dy = b.y - a.y;
  double dz = b.z - a.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

class union_find {
public:
  explicit union_find(size_t n) : size(n, 1), pred(n, 0), components(n) {
    for (size_t i = 0; i < n; ++i)
      pred[i] = i;
  }

public:
  size_t find(size_t n) {
    auto root = n;
    while (pred[root] != root) {
      root = pred[root];
    }

    // path compression -> a(n)
    auto curr = n;
    while (curr != root) {
      auto tmp = pred[curr];
      pred[curr] = root;
      curr = tmp;
    }

    return root;
  }

  void unify(size_t x, size_t y) {
    size_t root1 = find(x);
    size_t root2 = find(y);

    if (root1 == root2)
      return;
    if (size[root1] < size[root2]) {
      pred[root1] = root2;
      size[root2] += size[root1];
    } else {
      pred[root2] = root1;
      size[root1] += size[root2];
    }
    --components;
  }

  bool connected(size_t x, size_t y) { return find(x) == find(y); }
  size_t component_size(size_t n) { return size[find(n)]; }
  size_t total_connected_components() const { return components; }

private:
  std::vector<size_t> size;
  std::vector<size_t> pred;
  size_t components;
};

int main() {
  std::vector<vec3> boxes;

  int x, y, z;
  char a, b;
  while (std::cin >> x >> a >> y >> b >> z) {
    boxes.emplace_back(x, y, z);
  }

  std::vector<std::tuple<size_t, size_t, double>> costs;
  for (size_t i = 0; i < boxes.size(); ++i) {
    for (size_t j = i + 1; j < boxes.size(); ++j) {
      costs.emplace_back(i, j, dist(boxes[i], boxes[j]));
    }
  }

  std::sort(costs.begin(), costs.end(), [](const auto &a, const auto &b) {
    return std::get<2>(a) < std::get<2>(b);
  });

  union_find uf(boxes.size());
  size_t last_i = 0, last_j = 0;
  for (size_t i = 0; uf.total_connected_components() > 1; ++i) {
    auto [u, v, _] = costs[i];
    uf.unify(u, v);
    last_i = u;
    last_j = v;
  }

  std::cout << "ans = " << boxes[last_i].x * boxes[last_j].x << "\n";

  return 0;
}
