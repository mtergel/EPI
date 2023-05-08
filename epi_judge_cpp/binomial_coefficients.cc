#include "test_framework/generic_test.h"
#include <algorithm>
#include <vector>

using std::min;
using std::vector;

int ComputeBinomialCoefficient(int n, int k) {

  vector<int> dp(k + 1, 0);
  dp[0] = 1;

  for (int i = 1; i <= n; ++i) {
    for (int j = min(i, k); j > 0; --j) {
      dp[j] += dp[j - 1];
    }
  }

  return dp[k];

  // Tabulation
  // vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
  // for (int i = 0; i <= n; ++i) {
  //   for (int j = 0; j <= min(i, k); ++j) {
  //     if (j == 0 || j == i) {
  //       dp[i][j] = 1;
  //     } else {
  //       dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
  //     }
  //   }
  // }
  //
  // return dp[n][k];

  // Recursion
  // if (n == k || k == 0)
  //   return 1;
  //
  // return ComputeBinomialCoefficient(n - 1, k) +
  //        ComputeBinomialCoefficient(n - 1, k - 1);
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(
      args, "binomial_coefficients.cc", "binomial_coefficients.tsv",
      &ComputeBinomialCoefficient, DefaultComparator{}, param_names);
}
