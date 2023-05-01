#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::max;
using std::vector;

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int> &individual_play_scores) {
  // vector<vector<int>> dp(individual_play_scores.size(),
  //                        vector<int>(final_score + 1, 0));
  //
  // for (int i = 0; i < individual_play_scores.size(); ++i) {
  //
  //   dp[i][0] = 1; // base case
  //
  //   for (int j = 1; j <= final_score; ++j) {
  //
  //     int without_this_play =
  //         i >= 1 ? dp[i - 1][j] : 0; // without this play
  //                                    // get the previous result
  //
  //     int with_this_play =
  //         j >= individual_play_scores[i]             // if we can run this
  //             ? dp[i][j - individual_play_scores[i]] // the previous result
  //             : 0;                                   // can't run this play
  //
  //     dp[i][j] = without_this_play + with_this_play;
  //   }
  // }
  //
  // return dp[individual_play_scores.size() - 1][final_score];

  // O(sn) runtime, O(s) space
  vector<int> dp(final_score + 1, 0);
  dp[0] = 1;

  for (int i = 0; i < individual_play_scores.size(); ++i) {
    for (int j = 1; j <= final_score; ++j) {
      int without_this_play = i >= 1 ? dp[j] : 0;
      int with_this_play = j >= individual_play_scores[i]
                               ? dp[j - individual_play_scores[i]]
                               : 0;

      dp[j] = max(dp[j], without_this_play + with_this_play);
    }
  }

  return dp[final_score];

  // variant: count sequence
  // vector<int> dp(final_score + 1, 0);
  // dp[0] = 1;
  // for (int j = 1; j <= final_score; ++j) {
  //     for (const auto& s : individual_play_scores) {
  //         if (j - s) {
  //             dp[j] += dp[j - s];
  //         }
  //     }
  // }
  //
  // return dp[final_score];
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
