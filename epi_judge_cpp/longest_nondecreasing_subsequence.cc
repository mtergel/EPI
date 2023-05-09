#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"
using std::max;
using std::vector;

int LongestNondecreasingSubsequenceLength(const vector<int> &A) {
  vector<int> dp(A.size(), 1);

  for (int i = 1; i < A.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      if (A[i] >= A[j]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
  }

  return *std::max_element(dp.begin(), dp.end());
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_nondecreasing_subsequence.cc",
                         "longest_nondecreasing_subsequence.tsv",
                         &LongestNondecreasingSubsequenceLength,
                         DefaultComparator{}, param_names);
}
