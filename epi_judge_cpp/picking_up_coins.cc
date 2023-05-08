#include <vector>

#include "test_framework/generic_test.h"
using std::max;
using std::min;
using std::vector;

int helper(const vector<int> &coins, int a, int b,
           vector<vector<int>> *dp_ptr) {
  if (a > b) {
    return 0;
  }

  vector<vector<int>> &dp = *dp_ptr;
  if (dp[a][b] == 0) {
    // min represents that the opponent plays the best hand
    // so take the min of what the opponent plays
    int max_rev_a = coins[a] + min(helper(coins, a + 2, b, dp_ptr),
                                   helper(coins, a + 1, b - 1, dp_ptr));
    int max_rev_b = coins[b] + min(helper(coins, a + 1, b - 1, dp_ptr),
                                   helper(coins, a, b - 2, dp_ptr));

    dp[a][b] = max(max_rev_a, max_rev_b);
  }

  return dp[a][b];
}

int MaximumRevenue(const vector<int> &coins) {
  vector<vector<int>> dp(coins.size(), vector<int>(coins.size(), 0));

  return helper(coins, 0, coins.size() - 1, &dp);
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"coins"};
  return GenericTestMain(args, "picking_up_coins.cc", "picking_up_coins.tsv",
                         &MaximumRevenue, DefaultComparator{}, param_names);
}
