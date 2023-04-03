#include <functional>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"
using std::greater;
using std::priority_queue;
using std::vector;

vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {
  vector<int> res;
  priority_queue<int, vector<int>, greater<int>> pq;

  while (sequence_begin != sequence_end) {
    pq.emplace(*sequence_begin++);

    if (pq.size() == k) {
      res.emplace_back(pq.top());
      pq.pop();
    }
  }

  while (!pq.empty()) {
    res.emplace_back(pq.top());
    pq.pop();
  }

  return res;
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
