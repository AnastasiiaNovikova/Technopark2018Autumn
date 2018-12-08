#pragma once
#include <array>
#include <vector>

struct position {
  std::array<char, 9> chips;
  int zero_position;

  bool IsFinish() const;
  std::vector<position> Siblings() const;

  bool operator==(const position& other) const;
  bool operator!=(const position& other) const { return !operator==(other);}
};

const position kFinishPosition{{1, 2, 3, 4, 5, 6, 7, 8, 0}, 8};

namespace std {
  template<>
  struct hash<position> {
    size_t operator()(const position& pos) const {
      size_t hash = 0;
      for (const auto& chip: pos.chips) {
        hash = hash * 37 + chip;
      }
      return hash;
    }
  };
}
