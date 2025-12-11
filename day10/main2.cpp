#include <climits>
#include <iostream>
#include <sstream>
#include <string>
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

std::string build_lp_input(const Machine &m) {
  int rows = static_cast<int>(m.final_state.size());
  int cols = static_cast<int>(m.buttons.size());

  std::ostringstream out;
  out << rows << " " << cols << "\n";

  // A[i][j] = 1 if i is listed in buttons[j], else 0
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      int val = 0;
      for (int idx : m.buttons[j]) {
        if (idx == i) { // indices in buttons are 0-based row indices
          val = 1;
          break;
        }
      }
      out << val;
      if (j + 1 < cols)
        out << " ";
    }
    out << "\n";
  }

  // b from final_state characters
  for (int i = 0; i < rows; ++i) {
    out << m.voltage[i];
    if (i + 1 < rows)
      out << " ";
  }
  out << "\n";

  return out.str();
}

void process_machine(const Machine &m) {
  std::cout << build_lp_input(m);
  std::cout << "---\n";
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

    process_machine(data);
  }
  return 0;
}
