#include <assert.h>
#include <iostream>
#include <vector>

class DSU {
 public:
  explicit DSU(size_t size);

  int Find(int element);
  // element1 and element2 must be in different sets
  void Merge(int element1, int element2);

  void Print() const;

 private:
  int SimpleFind(int element) const;

    std::vector<int> parent;  // -1 if no parent
  std::vector<int> rank;
};

DSU::DSU(size_t size)
  : parent(size, -1),
    rank(size, 1) {}

int DSU::Find(int element) {
  if (parent[element] == -1) {
    return element;
  }
  return parent[element] = Find(parent[element]);
}

int DSU::SimpleFind(int element) const {
  while (parent[element] != -1) {
    element = parent[element];
  }
  return element;
}

void DSU::Merge(int element1, int element2) {
  const int presenter1 = Find(element1);
  const int presenter2 = Find(element2);
  assert(presenter1 != presenter2);

  if (rank[presenter1] > rank[presenter2]) {
    parent[presenter2] = presenter1;
  } else if (rank[presenter1] < rank[presenter2]) {
    parent[presenter1] = presenter2;
  } else {
    parent[presenter1] = presenter2;
    ++rank[presenter2];
  }
}

void DSU::Print() const {
  for (int i = 0; i < parent.size(); ++i) {
    std::cout << SimpleFind(i) << " ";
  }
  std::cout << std::endl;
}

int main() {
  DSU dsu(6);
  dsu.Print();
  dsu.Merge(2, 1);
  dsu.Merge(3, 4);
  dsu.Merge(5, 4);
  dsu.Print();
  dsu.Merge(2, 3);
  dsu.Print();
  dsu.Merge(0, 5);
  dsu.Print();
  return 0;
}