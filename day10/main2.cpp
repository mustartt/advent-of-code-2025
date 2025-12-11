#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

struct Machine {
  std::string final_state;
  std::vector<std::vector<int>> buttons;
  std::vector<int> voltage;

  void debug() {
    std::cout << "[" << final_state << "] ";
    for (const auto &t : buttons) {
      std::cout << "( ";
      for (size_t i = 0; i < t.size(); ++i) {
        std::cout << t[i] << " ";
      }
      std::cout << ") ";
    }
    std::cout << "{ ";
    for (size_t i = 0; i < voltage.size(); ++i) {
      std::cout << voltage[i] << " ";
    }
    std::cout << "}\n";
  }
};

void backtrack(std::span<int> state,
               const std::vector<std::vector<int>> &buttons, int depth,
               int &steps) {
  if (std::count(state.begin(), state.end(), 0) == state.size()) {
    steps = std::min(depth, steps);
    return;
  }
  for (const auto &button : buttons) {
    int min_val = 0;
    for (int pos : button) {
      min_val = std::min(min_val, --state[pos]);
    }
    if (min_val >= 0)
      backtrack(state, buttons, depth + 1, steps);

    for (int pos : button) {
      ++state[pos];
    }
  }
}

int process_machine(const Machine &m) {
  int steps = INT_MAX;

  std::vector<int> state = m.voltage;
  backtrack(state, m.buttons, 0, steps);

  return steps;
}

int main() {
  int total = 0;
  std::string line;
  while (std::getline(std::cin, line)) {

    std::stringstream ss(line);
    Machine data;
    char ch;

    ss >> std::ws;
    if (ss.peek() == '[') {
      ss >> ch;
      std::getline(ss, data.final_state, ']');
    }

    ss >> std::ws;
    while (ss.peek() == '(') {
      ss >> ch;

      std::vector<int> currentTuple;
      int num;

      while (ss >> num) {
        currentTuple.push_back(num);
        ss >> std::ws;
        if (ss.peek() == ',') {
          ss >> ch; // consume comma
        } else if (ss.peek() == ')') {
          break;
        }
      }
      ss >> ch;
      data.buttons.push_back(currentTuple);
      ss >> std::ws;
    }

    ss >> std::ws;
    if (ss.peek() == '{') {
      ss >> ch;
      int num;
      while (ss >> num) {
        data.voltage.push_back(num);
        ss >> std::ws;
        if (ss.peek() == ',') {
          ss >> ch;
        } else if (ss.peek() == '}') {
          break;
        }
      }
      ss >> ch;
    }

    data.debug();
    int n = process_machine(data);
    std::cout << "amount = " << n << "\n";
    total += n;
  }

  std::cout << "total = " << total << "\n";

  return 0;
}
