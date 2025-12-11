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

std::string toggle(const std::string &before, const std::vector<int> &button) {
  std::string result = before;
  for (size_t pos : button) {
    result[pos] = before[pos] == '#' ? '.' : '#';
  }
  return result;
}

int process_machine(const Machine &m) {
  int steps = 0;

  std::string start(m.final_state.size(), '.');
  std::queue<std::pair<std::string, int>> q;
  std::unordered_set<std::string> visited;
  visited.insert(start);
  q.emplace(std::move(start), 0);

  while (!q.empty()) {
    auto curr = std::move(q.front());
    q.pop();

    if (curr.first == m.final_state)
      return curr.second;

    for (const auto &button : m.buttons) {
      std::string next = toggle(curr.first, button);
      if (!visited.contains(next)) {
        visited.insert(next);
        q.emplace(std::move(next), curr.second + 1);
      }
    }
  }

  return -1;
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
