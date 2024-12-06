#include <iostream>
#include <unordered_set>

#include <utils.h>

constexpr int quest = 2;
constexpr int year = 2024;

struct Point {
  int x;
  int y;

  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
};

struct PointHash {
  std::size_t operator()(const Point &p) const {
    return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) * 31);
  }
};

void markSymbols(std::unordered_set<Point, PointHash> &symbols, const std::string &text,
                 const std::string &word, int coord, bool horizontal, bool wrap) {
  const std::regex regex(word);
  const std::string text2 = wrap ? (text + text) : text; // for wrapping
  auto end = wrap ? (text2.begin() + (int) text2.length() / 2) : text2.end();
  std::smatch match;
  for (auto i = text2.begin(); i != end && std::regex_search(i, text2.end(), match, regex); i += match.position() + 1) {
    for (auto j = 0; j < match.length(); ++j) {
      auto a = (j + match.position() + (i - text2.begin())) % text.length();
      Point p = horizontal ? Point((int) a, coord) : Point(coord, (int) a);
      symbols.insert(p);
    }
  }
}

void markSymbols(std::unordered_set<Point, PointHash> &symbols, const std::string &text,
                 const std::vector<std::string> &words, int coord, bool horizontal = true, bool wrap = false) {
  for (const auto &word: words) {
    markSymbols(symbols, text, word, coord, horizontal, wrap);
    const std::string reversed = std::string(word.rbegin(), word.rend());
    if (reversed != word) {
      markSymbols(symbols, text, reversed, coord, horizontal, wrap);
    }
  }
}

int solve1() {
  const ec::input input = ec::readInput<std::string>(year, quest, 1);
  const std::vector<std::string> words = ec::split(input[0].substr(6), std::regex(","));
  const std::string &text = input[2];

  int sum = 0;
  const auto end = std::sregex_iterator();
  for (auto &word: words) {
    std::regex regex(word);
    for (auto i = std::sregex_iterator(text.begin(), text.end(), regex); i != end; ++i, ++sum);
  }
  return sum;
}

int solve2() {
  const ec::input input = ec::readInput<std::string>(year, quest, 2);
  const std::vector<std::string> words = ec::split(input[0].substr(6), std::regex(","));

  std::unordered_set<Point, PointHash> symbols;
  for (int i = 2; i < input.size(); ++i) {
    markSymbols(symbols, input[i], words, i - 2);
  }

  return (int) symbols.size();
}

int solve3() {
  const ec::input input = ec::readInput<std::string>(year, quest, 3);
  const std::vector<std::string> words = ec::split(input[0].substr(6), std::regex(","));

  std::unordered_set<Point, PointHash> symbols;
  for (int i = 2; i < input.size(); ++i) {
    markSymbols(symbols, input[i], words, i - 2, true, true);
  }

  for (int i = 0; i < input[2].length(); ++i) {
    std::stringstream stream;
    for (int j = 2; j < input.size(); ++j) {
      stream << input[j][i];
    }
    markSymbols(symbols, stream.str(), words, i, false, false);
  }


  return (int) symbols.size();
}

int main() {
  std::cout << "Everybody Codes " << year << ", quest " << quest << std::endl;
  std::cout << "TASK 1: " << solve1() << std::endl;
  std::cout << "TASK 2: " << solve2() << std::endl;
  std::cout << "TASK 3: " << solve3() << std::endl;
}
