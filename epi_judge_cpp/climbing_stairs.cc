#include <iostream>
#include <vector>

int climb(int n, int k) {
  // DP
  std::vector<int> dp(n + 1, 0);
  dp[0] = 1;
  dp[1] = 1;

  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= k && j <= i; ++j) {
      dp[i] += dp[i - j];
    }
  }

  return dp[n];

  // Recursion
  // if (n <= 1) {
  //   return 1;
  // }
  //
  // int res = 0;
  // for (int i = 1; i <= k && i <= n; ++i) {
  //   res += climb(n - i, k);
  // }
  //
  // return res;
}

int main() {
  int res = climb(4, 3);

  std::cout << res << "\n";

  return res;
}
