#include <iostream>
#include <unordered_set>

#include <utils.h>
#include <point.h>

constexpr int quest = 3;
constexpr int year = 2024;

int solve(const int task) {
  const ec::input input = ec::readInput<std::string>(year, quest, task);

  std::unordered_set<aoc::Point, aoc::PointHash> set;

  for (int y = 0; y < input.size(); ++y) {
    for (int x = 0; x < input[0].size(); ++x) {
      if (input[y][x] == '#') {
        set.insert({x, y});
      }
    }
  }
  int sum = static_cast<int>(set.size());

  while (!set.empty()) {
    std::unordered_set<aoc::Point, aoc::PointHash> temp;
    for (auto &p: set) {
      if (set.contains({p.x + 1, p.y}) && set.contains({p.x, p.y + 1}) &&
          set.contains({p.x - 1, p.y}) && set.contains({p.x, p.y - 1}) &&
          (task != 3 || (set.contains({p.x + 1, p.y + 1}) && set.contains({p.x + 1, p.y - 1}) &&
                         set.contains({p.x - 1, p.y + 1}) && set.contains({p.x - 1, p.y - 1})))) {
        temp.insert(p);
      }
    }
    set = temp;
    sum += static_cast<int>(set.size());
  }

  return sum;
}

int main() {
  std::cout << "Everybody Codes " << year << ", quest " << quest << std::endl;
  std::cout << "TASK 1: " << solve(1) << std::endl;
  std::cout << "TASK 2: " << solve(2) << std::endl;
  std::cout << "TASK 3: " << solve(3) << std::endl;
}
