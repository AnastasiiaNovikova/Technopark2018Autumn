#include <iostream>

#include "list_graph.hpp"

int main() {
  ListGraph graph(4);
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 3);
  graph.AddEdge(2, 3);
  graph.AddEdge(2, 0);
  graph.AddEdge(1, 3);
  graph.AddEdge(3, 1);

  std::cout << "Vertices count = " << graph.VerticesCount() << std::endl;
  std::vector<int> prev_vertices;
  graph.GetPrevVertices(1, prev_vertices);
  std::cout << "In edges for a vertex 1 = ";
  for (int prev : prev_vertices) {
    std::cout << "(" << prev << ", 1), ";
  }
  std::cout << std::endl;

  graph.Print(std::cout);
  return 0;
}