#include <iostream>
#include <string>
#include <string_view>

std::pair<bool, int> parse_line(const std::string_view line) {
  char dir = line[0];
  int amount = std::atoi(line.data() + 1);
  return {dir == 'L', amount};
}

constexpr int count_crossing(int before, int after) {
  if (after >= before) {
    return after / 100;
  } else if (before == 0 || after > 0) {
    return (-after) / 100;
  }
  return (-after) / 100 + 1;
}

static_assert(count_crossing(0, 0) == 0);
static_assert(count_crossing(0, 50) == 0);
static_assert(count_crossing(0, 100) == 1);
static_assert(count_crossing(0, 150) == 1);
static_assert(count_crossing(0, 200) == 2);

static_assert(count_crossing(50, 50) == 0);
static_assert(count_crossing(50, 75) == 0);
static_assert(count_crossing(50, 100) == 1);
static_assert(count_crossing(50, 150) == 1);
static_assert(count_crossing(50, 200) == 2);

static_assert(count_crossing(0, 50) == 0);
static_assert(count_crossing(0, -50) == 0);
static_assert(count_crossing(0, -100) == 1);
static_assert(count_crossing(0, -150) == 1);
static_assert(count_crossing(0, -200) == 2);

static_assert(count_crossing(50, 45) == 0);
static_assert(count_crossing(50, 0) == 1);
static_assert(count_crossing(50, -50) == 1);
static_assert(count_crossing(50, -100) == 2);

int main() {
  int curr = 50;
  int password = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    auto [dir, amount] = parse_line(line);

    int before = curr;
    curr += dir ? -amount : amount;

    int cycle = count_crossing(before, curr);
    std::cout << "processing " << line << ": "
              << "before=" << before << " "
              << "curr=" << curr << " counted=" << cycle << "\n";

    curr = (curr % 100 + 100) % 100;
    password += cycle;
  }
  std::cout << "password = " << password << "\n";
  return 0;
}
