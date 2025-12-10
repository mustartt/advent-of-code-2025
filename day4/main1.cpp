#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

int count(const std::vector<std::string> &grid) {
  int n = grid.size();
  int m = grid[0].size();
  std::initializer_list<std::pair<int, int>> pos = {
      {-1, -1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}, {1, 1}, {0, -1}, {0, 1}};
  int total = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] != '@')
        continue;
      int cnt = 0;
      for (auto [di, dj] : pos) {
        if (i + di < 0 || j + dj < 0 || i + di >= n || j + dj >= m)
          continue;
        if (grid[i + di][j + dj] == '@')
          ++cnt;
      }
      if (cnt < 4)
        ++total;
    }
  }
  return total;
}

int main() {
  std::vector<std::string> grid;

  std::string line;
  while (std::getline(std::cin, line)) {
    grid.push_back(std::move(line));
  }

  std::cout << count(grid) << "\n";
  return 0;
}
