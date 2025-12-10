#include <iostream>
#include <string>
#include <vector>

constexpr std::initializer_list<std::pair<int, int>> pos = {
    {-1, -1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}, {1, 1}, {0, -1}, {0, 1}};

static int count_near(const std::vector<std::string> &grid, int i, int j) {
  int n = grid.size();
  int m = grid[0].size();
  int cnt = 0;

  for (auto [di, dj] : pos) {
    if (i + di < 0 || j + dj < 0 || i + di >= n || j + dj >= m)
      continue;
    if (grid[i + di][j + dj] == '@')
      ++cnt;
  }
  return cnt;
}

static int remove(std::vector<std::string> &grid) {
  int removed = 0;
  int n = grid.size();
  int m = grid[0].size();

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == '@' && count_near(grid, i, j) < 4) {
        ++removed;
        grid[i][j] = 'x';

        /*
        for (const auto &row : grid) {
          std::cout << row << "\n";
        }
        std::cout << "\n" << std::endl;
        */
      }
    }
  }

  return removed;
}

int main() {
  std::vector<std::string> grid;

  std::string line;
  while (std::getline(std::cin, line)) {
    grid.push_back(std::move(line));
  }

  int removed = 0;
  while (int cnt = remove(grid)) {
    removed += cnt;
  }
  std::cout << "removed = " << removed << "\n";

  return 0;
}
