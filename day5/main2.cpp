#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::pair<long, long>> ranges;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty())
      continue;

    auto idx = line.find('-');
    if (idx == std::string::npos)
      continue;

    auto first = std::stol(line.substr(0, idx));
    auto second = std::stol(line.substr(idx + 1));
    ranges.emplace_back(first, second);
  }

  std::sort(ranges.begin(), ranges.end());

  long total = 0;
  long curr_start = -1;
  long curr_end = -2;

  for (size_t i = 0; i < ranges.size(); ++i) {
    long start = ranges[i].first;
    long end = ranges[i].second;
    if (curr_end < start) {
      long len = curr_end - curr_start + 1;
      curr_start = start;
      curr_end = end;
      total += len;
    } else {
      curr_end = std::max(curr_end, end);
    }
  }
  long len = curr_end - curr_start + 1;
  total += len;

  std::cout << "total = " << total << "\n";

  return 0;
}
