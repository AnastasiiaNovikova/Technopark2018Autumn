#include <iostream>

#include "puzzle8.hpp"

int main() {
//  position start{{1, 2, 3, 4, 5, 6, 8, 7, 0}, 8};
//  position start{{1, 2, 3, 5, 7, 6, 4, 0, 8}, 7};
  position start{{3, 5, 6, 1, 0, 2, 7, 8, 4}, 4};
//  position start{{8, 7, 6, 5, 4, 3, 2, 1, 0}, 8};
  const auto solution = SolvePuzzle8(start);
  std::cout << solution.first << std::endl << solution.second << std::endl;
  return 0;
}