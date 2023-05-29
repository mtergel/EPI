#include <algorithm>
#include <stdexcept>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::vector;

struct GraphVertex {
  enum Color { WHITE, GRAY, BLACK } color = WHITE;
  vector<GraphVertex *> edges;
};

bool helper(GraphVertex *curr) {
  if (curr->color == GraphVertex::GRAY) {
    return true;
  }

  curr->color = GraphVertex::GRAY;
  for (auto &next : curr->edges) {
    if (next->color != GraphVertex::BLACK) {
      if (helper(next)) {
        return true;
      }
    }
  }

  curr->color = GraphVertex::BLACK;

  return false;
}

bool IsDeadlocked(vector<GraphVertex> *graph) {
  // detect cycle using 3 colored dfs
  // white not visited, gray currently visiting, black visited

  return std::any_of(graph->begin(), graph->end(), [](GraphVertex &vertex) {
    return vertex.color == GraphVertex::WHITE && helper(&vertex);
  });
}
struct Edge {
  int from;
  int to;
};

namespace test_framework {
template <> struct SerializationTrait<Edge> : UserSerTrait<Edge, int, int> {};
} // namespace test_framework

bool HasCycleWrapper(TimedExecutor &executor, int num_nodes,
                     const vector<Edge> &edges) {
  vector<GraphVertex> graph;
  if (num_nodes <= 0) {
    throw std::runtime_error("Invalid num_nodes value");
  }
  graph.reserve(num_nodes);

  for (int i = 0; i < num_nodes; i++) {
    graph.push_back(GraphVertex{});
  }

  for (const Edge &e : edges) {
    if (e.from < 0 || e.from >= num_nodes || e.to < 0 || e.to >= num_nodes) {
      throw std::runtime_error("Invalid vertex index");
    }
    graph[e.from].edges.push_back(&graph[e.to]);
  }

  return executor.Run([&] { return IsDeadlocked(&graph); });
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_nodes", "edges"};
  return GenericTestMain(args, "deadlock_detection.cc",
                         "deadlock_detection.tsv", &HasCycleWrapper,
                         DefaultComparator{}, param_names);
}
