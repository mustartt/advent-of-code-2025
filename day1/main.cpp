#include <iostream>
#include <string>
#include <string_view>

std::pair<bool, int> parse_line(const std::string_view line) {
  char dir = line[0];
  int amount = std::atoi(line.data() + 1);
  return {dir == 'L', amount};
}

int main() {
  int curr = 50;
  int password = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    auto [dir, amount] = parse_line(line);
    curr += dir ? -amount : amount;
    if (curr < 0)
      curr += 100;
    curr %= 100;
    if (curr == 0)
      ++password;
  }
  std::cout << "password = " << password << "\n";
  return 0;
}
