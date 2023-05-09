#include <climits>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::min;
using std::string;
using std::vector;

int MinimumMessiness(const vector<string> &words, int line_length) {
  // dp[i] is the minimal messiness when placing words [0 : i]
  vector<int> dp(words.size(), INT_MAX);

  // base case, 0 indexed dp
  int blanks = line_length - words[0].size();
  dp[0] = blanks * blanks;

  for (int i = 1; i < words.size(); ++i) {
    blanks = line_length - words[i].size();
    dp[i] = dp[i - 1] + blanks * blanks; // base case, new line

    // try adding words, previous words
    for (int j = i - 1; j >= 0; --j) {
      blanks -= (words[j].size() + 1); // space between words
      if (blanks < 0) {
        // no more space
        break;
      }

      // Once a minimum cost partition of words to a set of lines has
      // been discovered, the inclusion of
      // additional words can only alter the configuration of the last line

      // Furthermore, since the first i words are assumed to be optimally
      // placed, the placement of words on the lines prior to the last one must
      // be optimum.
      int first_j_messiness = j > 0 ? dp[j - 1] : 0;

      // Current messiness including this word
      int curr_messiness = blanks * blanks;

      dp[i] = min(dp[i], first_j_messiness + curr_messiness);
    }
  }

  return dp.back();
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"words", "line_length"};
  return GenericTestMain(args, "pretty_printing.cc", "pretty_printing.tsv",
                         &MinimumMessiness, DefaultComparator{}, param_names);
}
