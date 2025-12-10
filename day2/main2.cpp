#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

static bool is_invalid(long long id) {
  std::string value = std::to_string(id);

  std::string_view sv = value;
  for (size_t len = 1; len < sv.size(); ++len) {
    if (sv.size() % len != 0 || sv.size() / len < 2)
      continue;
    auto pattern = sv.substr(0, len);
    bool all_same = true;
    for (size_t i = 1; i < sv.size() / len; ++i) {
      if (pattern != sv.substr(i * len, len)) {
        all_same = false;
        break;
      }
    }

    if (all_same)
      return true;
  }
  return false;
}

int main() {
  long long ans = 0;

  std::string input;
  std::getline(std::cin, input);
  input.push_back(',');
  std::istringstream in(input);

  std::string range;
  while (std::getline(in, range, ',')) {
    auto idx = range.find('-');
    auto start = std::stoll(range.substr(0, idx));
    auto end = std::stoll(range.substr(idx + 1));
    for (long long i = start; i <= end; ++i) {
      if (is_invalid(i)) {
        std::cout << i << "\n";
        ans += i;
      }
    }
  }
  std::cout << "ans = " << ans << "\n";

  return 0;
}
