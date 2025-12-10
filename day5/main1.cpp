#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string line;

  std::vector<std::pair<long, long>> ranges;
  std::vector<long> queries;

  while (std::getline(std::cin, line)) {
    if (line.empty())
      continue;
    auto idx = line.find('-');
    if (idx != std::string::npos) {
      auto first = std::stol(line.substr(0, idx));
      auto second = std::stol(line.substr(idx + 1));
      ranges.emplace_back(first, second);
    } else {
      queries.push_back(std::stol(line));
    }
  }

  std::sort(ranges.begin(), ranges.end());
  std::sort(queries.begin(), queries.end());

  int total = 0;
  for (auto n : queries) {
    std::cout << n << "\n";
    for (const auto &[start, end] : ranges) {
      if (start <= n && n <= end) {
        std::cout << "  fresh \n";
        ++total;
        break;
      }
    }
  }

  std::cout << "total = " << total << "\n";

  return 0;
}
