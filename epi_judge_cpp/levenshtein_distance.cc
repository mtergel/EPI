#include <algorithm>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::fill;
using std::min;
using std::string;
using std::swap;
using std::vector;

int LevenshteinDistance(const string &A, const string &B) {
  // Space Optimized
  // Each time we update dp[i][j]
  // we only need dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]
  int m = A.size(), n = B.size();
  vector<int> prev(n + 1, 0), curr(n + 1, 0);
  for (int j = 1; j <= n; ++j) {
    prev[j] = j;
  }

  for (int i = 1; i <= m; ++i) {
    curr[0] = i;
    for (int j = 1; j <= n; ++j) {
      if (A[i - 1] == B[j - 1]) {
        curr[j] = prev[j - 1];
      } else {
        curr[j] = 1 + min({prev[j - 1], curr[j - 1], prev[j]});
      }
    }

    fill(prev.begin(), prev.end(), 0);
    swap(prev, curr);
  }

  return prev[n];

  // int m = A.size(), n = B.size();
  // vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  //
  // // base cases
  // for (int i = 1; i <= m; ++i) {
  //   dp[i][0] = i;
  // }
  //
  // for (int j = 1; j <= n; ++j) {
  //   dp[0][j] = j;
  // }
  //
  // for (int i = 1; i <= m; ++i) {
  //   for (int j = 1; j <= n; ++j) {
  //     if (A[i - 1] == B[j - 1]) {
  //       dp[i][j] = dp[i - 1][j - 1]; // same letter use prev
  //     } else {
  //       // in order
  //       // replace, insert, delete
  //       dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]});
  //     }
  //   }
  // }
  //
  // return dp[m][n];

  // // variant: longest subseq
  // vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  // for (int i = 1; i <= m; ++i) {
  //   for (int j = 1; j <= n; ++j) {
  //     if (A[i - 1] == B[j - 1]) {
  //       // found same letter
  //       // increase the subseq
  //       dp[i][j] = dp[i - 1][j - 1] + 1;
  //     } else {
  //       // not same letter
  //       // so retain the prev result
  //       dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
  //     }
  //   }
  // }
  //
  // return dp[m][n];

  // variant: given a string a, compute the minimum number of characters you
  // need to delete from a to make the resulting string a palindrome
  //
  // Find the longest subseq with reversed string, x
  // x - len(a)
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
