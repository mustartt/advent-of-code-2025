#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<std::pair<long, long>> pos;
  long x, y;
  char p;
  while (std::cin >> x >> p >> y) {
    std::cout << x << " " << y << "\n";
    pos.emplace_back(x, y);
  }

  long max_area = 0;
  for (size_t i = 0; i < pos.size(); ++i) {
    for (size_t j = i + 1; j < pos.size(); ++j) {
      auto [a, b] = pos[i];
      auto [u, v] = pos[j];
      long area = (std::abs(a - u) + 1) * (std::abs(b - v) + 1);
      max_area = std::max(max_area, area);
    }
  }

  std::cout << "area = " << max_area << "\n";

  return 0;
}
