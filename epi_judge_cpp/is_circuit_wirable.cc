#include <queue>
#include <stdexcept>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::queue;
using std::vector;

struct GraphVertex {
  int d = -1;
  vector<GraphVertex *> edges;
};

bool helper(GraphVertex *s) {
  queue<GraphVertex *> q;
  q.push(s);

  while (!q.empty()) {
    for (auto &neigh : q.front()->edges) {
      if (neigh->d == -1) {
        neigh->d = q.front()->d + 1;
        q.push(neigh);
      } else if (neigh->d == q.front()->d) {
        return false;
      }
    }
    q.pop();
  }

  return true;
}

bool IsAnyPlacementFeasible(vector<GraphVertex> *G) {
  for (GraphVertex &v : *G) {
    if (v.d == -1) {
      v.d = 0;
      if (!helper(&v)) {
        return false;
      }
    }
  }

  return true;
}
struct Edge {
  int from;
  int to;
};

namespace test_framework {
template <> struct SerializationTrait<Edge> : UserSerTrait<Edge, int, int> {};
} // namespace test_framework

bool IsAnyPlacementFeasibleWrapper(TimedExecutor &executor, int k,
                                   const vector<Edge> &edges) {
  vector<GraphVertex> graph;
  if (k <= 0) {
    throw std::runtime_error("Invalid k value");
  }
  graph.reserve(k);

  for (int i = 0; i < k; i++) {
    graph.push_back(GraphVertex{});
  }

  for (auto &e : edges) {
    if (e.from < 0 || e.from >= k || e.to < 0 || e.to >= k) {
      throw std::runtime_error("Invalid vertex index");
    }
    graph[e.from].edges.push_back(&graph[e.to]);
  }

  return executor.Run([&] { return IsAnyPlacementFeasible(&graph); });
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "k", "edges"};
  return GenericTestMain(
      args, "is_circuit_wirable.cc", "is_circuit_wirable.tsv",
      &IsAnyPlacementFeasibleWrapper, DefaultComparator{}, param_names);
}
