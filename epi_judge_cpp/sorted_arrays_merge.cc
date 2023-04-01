#include <functional>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"
using std::greater;
using std::priority_queue;
using std::vector;

struct IteratorCurrentAndEnd {
  bool operator>(const IteratorCurrentAndEnd& that) const {
    return *current > *that.current;
  }

  vector<int>::const_iterator current;
  vector<int>::const_iterator end;
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  priority_queue<IteratorCurrentAndEnd, vector<IteratorCurrentAndEnd>,
                 greater<>>
      min_heap;

  for (const vector<int>& sorted_array : sorted_arrays) {
    if (!sorted_array.empty()) {
      min_heap.emplace(
          IteratorCurrentAndEnd{sorted_array.cbegin(), sorted_array.cend()});
    }
  }

  vector<int> res;
  while (!min_heap.empty()) {
    auto smallest = min_heap.top();
    min_heap.pop();

    if (smallest.current != smallest.end) {
      res.emplace_back(*smallest.current);
      min_heap.emplace(
          IteratorCurrentAndEnd{next(smallest.current), smallest.end});
    }
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
