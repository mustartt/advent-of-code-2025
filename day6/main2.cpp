#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

static long compute(const std::vector<std::string_view> col, char op) {
  size_t width = col[0].size();
  std::cout << width << "\n";

  std::vector<int> curr;
  for (size_t i = 0; i < width; ++i) {
    int num = 0;
    size_t m = 1;
    for (std::string_view sv : col | std::views::reverse) {
      if (sv[i] == ' ')
        continue;
      int digit = sv[i] - '0';
      num += m * static_cast<size_t>(digit);
      m *= 10;
    }
    std::cout << num << " ";
    curr.push_back(num);
  }
  std::cout << "\n";

  if (op == '*') {
    return std::accumulate(curr.begin(), curr.end(), 1L, std::multiplies<>());
  } else {
    return std::accumulate(curr.begin(), curr.end(), 0L, std::plus<>());
  }
}

int main() {
  std::vector<std::string> data;
  std::string ops;

  std::string line;
  std::string word;
  while (std::getline(std::cin, line)) {
    if (line.empty())
      continue;
    if (line[0] == '+' || line[0] == '*') {
      ops = std::move(line);
    } else {
      data.push_back(std::move(line));
    }
  }

  size_t start = 0;
  std::vector<std::pair<size_t, size_t>> pos;

  for (size_t i = 1; i < ops.size(); ++i) {
    if (ops[i] != ' ') {
      pos.emplace_back(start, i - 1);
      start = i;
    }
  }
  pos.emplace_back(start, ops.size());

  long total = 0;
  for (const auto &[a, b] : pos) {
    std::vector<std::string_view> col;
    for (size_t row = 0; row < data.size(); ++row) {
      std::string_view sv = data[row];
      col.push_back(sv.substr(a, b - a));
    }
    total += compute(col, ops[a]);
  }

  std::cout << "total = " << total << "\n";

  return 0;
}
