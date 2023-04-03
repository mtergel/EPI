#include <functional>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"
using std::greater;
using std::priority_queue;
using std::vector;

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator& sequence_end) {
  vector<double> res;
  priority_queue<int> max_heap;
  priority_queue<int, vector<int>, greater<int>> min_heap;

  while (sequence_begin != sequence_end) {
    min_heap.emplace(*sequence_begin++);
    max_heap.emplace(min_heap.top());
    min_heap.pop();

    if (max_heap.size() > min_heap.size()) {
      min_heap.emplace(max_heap.top());
      max_heap.pop();
    }

    res.emplace_back(min_heap.size() == max_heap.size()
                         ? 0.5 * (min_heap.top() + max_heap.top())
                         : min_heap.top());
  }

  return res;
}
vector<double> OnlineMedianWrapper(const vector<int>& sequence) {
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
