#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

static bool is_invalid(long long id) {
  std::string value = std::to_string(id);
  if (value.size() % 2 != 0)
    return false;
  std::string_view sv = value;
  size_t mid = sv.size() / 2;
  return sv.substr(0, mid) == sv.substr(mid, mid);
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
        ans += i;
      }
    }
  }
  std::cout << "ans = " << ans << "\n";

  return 0;
}
