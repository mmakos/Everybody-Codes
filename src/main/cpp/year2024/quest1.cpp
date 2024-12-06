#include <iostream>
#include <algorithm>

#include <utils.h>

constexpr int quest = 1;
constexpr int year = 2024;

int getPotionsForEnemy(char enemy) {
  switch (enemy) {
    case 'A':
      return 0;
    case 'B':
      return 1;
    case 'C':
      return 3;
    case 'D':
      return 5;
    default:
      return -1;
  }
}

int getPotionsForEnemies(std::string::const_iterator &it, int length) {
  int potions = 0;
  int enemies = 0;
  for (int i = 0; i < length; ++i, ++it) {
    int pots = getPotionsForEnemy(*it);
    if (pots >= 0) {
      potions += pots;
      ++enemies;
    }
  }
  return potions + enemies * (enemies - 1);
}

int solve(int task) {
  const std::string input = ec::readInput<std::string>(year, quest, task)[0];
  int sum = 0;
  auto it = input.begin();
  while (it != input.end()) {
    sum += getPotionsForEnemies(it, task);
  }
  return sum;
}

int main() {
  std::cout << "Everybody Codes " << year << ", quest " << quest << std::endl;
  std::cout << "TASK 1: " << solve(1) << std::endl;
  std::cout << "TASK 2: " << solve(2) << std::endl;
  std::cout << "TASK 3: " << solve(3) << std::endl;
}
