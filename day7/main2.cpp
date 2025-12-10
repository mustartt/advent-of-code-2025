#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
int main() {
  std::vector<std::string> data;

  std::string line;
  while (std::getline(std::cin, line)) {
    data.push_back(std::move(line));
  }

  size_t width = data[0].size();
  std::vector<long> prev(width, 0);
  std::vector<long> curr(width, 0);

  auto it = std::find(data[0].begin(), data[0].end(), 'S');

  prev[static_cast<size_t>(it - data[0].begin())] = 1;

  for (size_t i = 0; i + 1 < data.size(); ++i) {
    for (size_t j = 0; j < width; ++j) {
      if (prev[j] && data[i + 1][j] == '^') {
        if (j > 0) {
          curr[j - 1] += prev[j];
          data[i + 1][j - 1] = '|';
        }
        if (j + 1 < width) {
          curr[j + 1] += prev[j];
          data[i + 1][j + 1] = '|';
        }
      } else if (prev[j]) {
        curr[j] += prev[j];
        data[i + 1][j] = '|';
      }
    }
    std::swap(prev, curr);
    std::fill(curr.begin(), curr.end(), 0);
  }

  for (const auto &row : data) {
    std::cout << row << "\n";
  }

  long splits = std::accumulate(prev.begin(), prev.end(), 0L);

  std::cout << "ans = " << splits << "\n";
  return 0;
}
