#include "list_graph.hpp"

#include <assert.h>
#include <iostream>

ListGraph::ListGraph(size_t vertices_count)
    : out_edges_(vertices_count),
      in_edges_(vertices_count) {}

void ListGraph::AddEdge(int from, int to) {
  assert(from >= 0 && from < VerticesCount());
  assert(to >= 0 && to < VerticesCount());

  // No checks (multigraph)
  out_edges_[from].push_back(to);
  in_edges_[to].push_back(from);
}

void ListGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
  assert(vertex >= 0 && vertex < VerticesCount());
  vertices = out_edges_[vertex];
}

void ListGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
  assert(vertex >= 0 && vertex < VerticesCount());
  vertices = in_edges_[vertex];
}

void ListGraph::Print(std::ostream& out) {
  out << "Out_edges" << std::endl;
  for (int i = 0; i < out_edges_.size(); ++i) {
    out << i << ": ";
    for (int out_target : out_edges_[i]) {
      out << out_target << " ";
    }
    out << std::endl;
  }
}
