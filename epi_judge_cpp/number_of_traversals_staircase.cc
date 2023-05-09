#include "test_framework/generic_test.h"
#include <vector>

using std::vector;

int NumberOfWaysToTop(int top, int maximum_step) {
  vector<int> dp(top + 1, 0);
  dp[0] = 1;
  dp[1] = 1;

  for (int i = 2; i <= top; ++i) {
    for (int j = 1; j <= maximum_step && j <= i; ++j) {
      dp[i] += dp[i - j];
    }
  }

  return dp[top];
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"top", "maximum_step"};
  return GenericTestMain(args, "number_of_traversals_staircase.cc",
                         "number_of_traversals_staircase.tsv",
                         &NumberOfWaysToTop, DefaultComparator{}, param_names);
}
