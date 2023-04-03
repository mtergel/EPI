#include <functional>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"

using std::function;
using std::priority_queue;
using std::vector;

vector<int> KLargestInBinaryHeap(const vector<int>& A, int k) {
  if (k <= 0) {
    return {};
  }

  struct HeapEntry {
    int index, value;
  };

  priority_queue<HeapEntry, vector<HeapEntry>,
                 function<bool(HeapEntry, HeapEntry)>>
      candidate_max_heap([](const HeapEntry& a, const HeapEntry& b) {
        return a.value < b.value;
      });

  // largest element
  candidate_max_heap.emplace(HeapEntry{0, A[0]});
  vector<int> res;

  for (int i = 0; i < k; ++i) {
    int candidate_idx = candidate_max_heap.top().index;
    res.emplace_back(A[candidate_idx]);
    candidate_max_heap.pop();

    // check its children
    int left_child_idx = 2 * candidate_idx + 1;
    if (left_child_idx < A.size()) {
      candidate_max_heap.emplace(HeapEntry{left_child_idx, A[left_child_idx]});
    }

    int right_child_idx = 2 * candidate_idx + 2;
    if (right_child_idx < A.size()) {
      candidate_max_heap.emplace(
          HeapEntry{right_child_idx, A[right_child_idx]});
    }
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "k_largest_in_heap.cc", "k_largest_in_heap.tsv",
                         &KLargestInBinaryHeap, UnorderedComparator{},
                         param_names);
}
