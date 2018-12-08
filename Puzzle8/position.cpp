#include "position.hpp"

#include <utility>

bool position::IsFinish() const {
  return operator==(kFinishPosition);
}

std::vector<position> position::Siblings() const {
  std::vector<position> siblings;
  if (zero_position >= 3) {
    const int new_zero_position = zero_position - 3;
    position down{chips, new_zero_position};
    std::swap(down.chips[zero_position], down.chips[new_zero_position]);
    siblings.emplace_back(down);
  }
  if (zero_position <= 5) {
    const int new_zero_position = zero_position + 3;
    position up{chips, new_zero_position};
    std::swap(up.chips[zero_position], up.chips[new_zero_position]);
    siblings.emplace_back(up);
  }
  if (zero_position % 3 >= 1) {
    const int new_zero_position = zero_position - 1;
    position right{chips, new_zero_position};
    std::swap(right.chips[zero_position], right.chips[new_zero_position]);
    siblings.emplace_back(right);
  }
  if (zero_position %3 <= 1) {
    const int new_zero_position = zero_position + 1;
    position left{chips, new_zero_position};
    std::swap(left.chips[zero_position], left.chips[new_zero_position]);
    siblings.emplace_back(left);
  }
  return siblings;
}

bool position::operator==(const position& other) const {
  return chips == other.chips;
  // Zero position must be equal for equal chips
}
