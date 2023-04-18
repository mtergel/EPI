#include <algorithm>
#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
using std::max;
using std::unordered_set;
using std::vector;

int LongestContainedRange(const vector<int>& A) {
  unordered_set<int> curr(A.begin(), A.end());

  int res = 0;
  while (!curr.empty()) {
    int a = *curr.begin();
    curr.erase(a);

    int lower_bound = a - 1;
    while (curr.count(lower_bound)) {
      curr.erase(lower_bound);
      --lower_bound;
    }

    int upper_bound = a + 1;
    while (curr.count(upper_bound)) {
      curr.erase(upper_bound);
      ++upper_bound;
    }

    res = max(res, upper_bound - lower_bound - 1);
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "longest_contained_interval.cc", "longest_contained_interval.tsv",
      &LongestContainedRange, DefaultComparator{}, param_names);
}
