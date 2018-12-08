#include "puzzle8.hpp"

#include <assert.h>
#include <queue>
#include <unordered_map>

char GetTurnSymbol(const position& from, const position& to) {
  const int zero_position_diff = to.zero_position - from.zero_position;
  switch (zero_position_diff) {
    case 3: return 'U';
    case -3: return 'D';
    case 1: return 'L';
    case -1: return 'R';
    default: assert(false);
  }
}

bool Bfs(const position& start, std::unordered_map<position, position>& parents) {
  std::queue<position> bfs_queue;
  bfs_queue.push(start);
  while (!bfs_queue.empty()) {
    position current = bfs_queue.front(); bfs_queue.pop();
    for (const position& pos: current.Siblings()) {
      if (!parents.count(pos)) {
        parents.emplace(pos, current);
        if (pos.IsFinish()) {
          return true;
        }
        bfs_queue.push(pos);
      }
    }
  }
  return false;
}

std::string GetPath(const position& start,
    const std::unordered_map<position, position>& parents) {
  std::string path;
  position current = kFinishPosition;
  while (current != start) {
    position parent = parents.at(current);
    path.push_back(GetTurnSymbol(parent, current));
    current = parent;
  }
  std::reverse(path.begin(), path.end());
  return path;
}

std::pair<int, std::string> SolvePuzzle8(const position& start) {
  std::unordered_map<position, position> parents;
  if (!Bfs(start, parents)) {
    return std::make_pair(-1, std::string());
  }
  const std::string path = GetPath(start, parents);
  return std::make_pair(path.size(), path);
}