#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
int main() {
  std::vector<std::string> data;

  std::string line;
  while (std::getline(std::cin, line)) {
    data.push_back(std::move(line));
  }

  int splits = 0;
  size_t width = data[0].size();
  std::vector<bool> prev(width, false);
  std::vector<bool> curr(width, false);

  auto it = std::find(data[0].begin(), data[0].end(), 'S');
  prev[static_cast<size_t>(it - data[0].begin())] = true;

  for (size_t i = 0; i + 1 < data.size(); ++i) {
    for (size_t j = 0; j < width; ++j) {
      if (prev[j] && data[i + 1][j] == '^') {
        ++splits;
        if (j > 0) {
          curr[j - 1] = true;
          data[i + 1][j - 1] = '|';
        }
        if (j + 1 < width) {
          curr[j + 1] = true;
          data[i + 1][j + 1] = '|';
        }
      } else if (prev[j]) {
        curr[j] = true;
        data[i + 1][j] = '|';
      }
    }
    std::swap(prev, curr);
    std::fill(curr.begin(), curr.end(), false);
  }

  for (const auto &row : data) {
    std::cout << row << "\n";
  }

  std::cout << "ans = " << splits << "\n";
  return 0;
}
