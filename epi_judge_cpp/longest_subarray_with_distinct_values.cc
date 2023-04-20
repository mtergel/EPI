#include <algorithm>
#include <cstddef>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
using std::unordered_map;
using std::vector;

int LongestSubarrayWithDistinctEntries(const vector<int>& A) {
  if (A.empty()) return 0;

  // num <-> recent occurrence
  unordered_map<int, size_t> m;
  size_t res = 0;
  size_t l = 0;

  for (size_t r = 0; r < A.size(); ++r) {
    auto dup_idx = m.emplace(A[r], r);

    // duplicate
    if (!dup_idx.second) {
      // is A[r] in longest current subarray?
      if (dup_idx.first->second >= l) {
        res = std::max(res, r - l);
        l = dup_idx.first->second + 1;
      }
    }

    dup_idx.first->second = r;
  }

  return std::max(res, A.size() - l);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_subarray_with_distinct_values.cc",
                         "longest_subarray_with_distinct_values.tsv",
                         &LongestSubarrayWithDistinctEntries,
                         DefaultComparator{}, param_names);
}
