#include "test_framework/generic_test.h"
#include <vector>

using std::vector;

int NumberOfWays(int n, int m) {
  // space optimized
  vector<int> curr(m, 1);

  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      curr[j] += curr[j - 1];
    }
  }

  return curr[m - 1];

  // vector<vector<int>> dp(n, vector<int>(m, 1));
  //
  // for (int i = 1; i < n; ++i) {
  //   for (int j = 1; j < m; ++j) {
  //     dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
  //   }
  // }
  //
  // return dp[n - 1][m - 1];

  // variant: with obstacle
  // check start, if it has obstacle or dp[0][0] = 1
  // fill the first row, col using the dp and obstacles
  // then repeat top solution + with obstacles
  // dp[i][j] = obstacle[i][j] ? 0 : dp[i - 1][j] + dp[i][j - 1];

  // variant: with fisherman, max path
  // compute the max values for the first row, col
  // then use dp, dp[i][j] = fish[i][j] + max(dp[i - 1][j], dp[i][j - 1]);

  // variant: fisherman can start and end at any point
  // check if it is possible to reach end from start
  // do the same?

  // variant: given k, compute the number of decimal numbers of len k that are
  // monotone D[i] <= D[i + 1]
  // 2d dp with k len and 1-9 digits, fill first row, col and
  // dp[i][j] = dp[i - 1][j - 1]

  // variant: same as top but D[i] < D[i + 1] its strict now
  // can't take duplicates so
  // dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1]
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
