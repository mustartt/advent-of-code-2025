#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::vector<std::vector<int>> data;
  std::vector<char> operations;

  std::string line;
  std::string word;
  while (std::getline(std::cin, line)) {
    if (line.empty())
      continue;
    std::istringstream words(line);

    if (line[0] == '*' || line[0] == '+') {
      char c;
      while (words >> c) {
        operations.push_back(c);
      }
    } else {
      data.push_back({});
      int num;
      while (words >> num) {
        data.back().push_back(num);
      }
    }
  }

  long total = 0;
  for (size_t col = 0; col < operations.size(); ++col) {
    long curr = data[0][col];
    for (size_t row = 1; row < data.size(); ++row) {
      if (operations[col] == '+') {
        curr += data[row][col];
      } else {
        curr *= data[row][col];
      }
    }
    total += curr;
  }

  std::cout << total << std::endl;

  return 0;
}
