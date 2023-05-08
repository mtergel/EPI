#include <string>
#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::reverse;
using std::string;
using std::unordered_set;
using std::vector;

vector<string>
DecomposeIntoDictionaryWords(const string &domain,
                             const unordered_set<string> &dictionary) {
  vector<string> res;

  // -1 means not decomposeable
  vector<int> last_len(domain.size(), -1);

  for (int i = 0; i < domain.size(); ++i) {

    // check if whole substring is dictionary word
    if (dictionary.find(domain.substr(0, i + 1)) != dictionary.cend()) {
      last_len[i] = i + 1;
    }

    // if its not a dictionary word
    if (last_len[i] == -1) {

      // check if it is decomposeable
      for (int j = 0; j < i; ++j) {
        // if (0, j + 1) is decomposable word
        // and substring(j + 1, i - j) is an dictionary word
        if (last_len[j] != -1 &&
            dictionary.find(domain.substr(j + 1, i - j)) != dictionary.cend()) {
          last_len[i] = i - j;
          break;
        }
      }
    }
  }

  if (last_len.back() != -1) {
    int idx = domain.size() - 1;
    while (idx >= 0) {
      res.push_back(domain.substr(idx + 1 - last_len[idx], last_len[idx]));
      idx -= last_len[idx];
    }

    reverse(res.begin(), res.end());
  }

  // Variant: palindrome partitioning with minimal cuts
  // can use the same solution uptop but it is slow repeated palindromic checks
  //
  // can use 2 dp array, one for cuts and one for palindromic strings to cache
  // results, here if s[start] == s[end] && (end - start <= 2 || dp[start +
  // 1][end - 1])
  //
  // Crackhead solution:
  // string s = "0204451881";
  // int n = s.size();
  // vector<int> dp(n + 1, 0);
  // std::iota(dp.begin(), dp.end(), -1);
  //
  // for (int i = 0; i < n; ++i) {
  //   // odd
  //   for (int j = 0; i - j >= 0 && i + j < n && s[i - j] == s[i + j]; ++j) {
  //     dp[i + j + 1] = std::min(dp[i + j + 1], dp[i - j] + 1);
  //   }
  //
  //   // even
  //   for (int j = 0; i - j + 1 >= 0 && i + j < n && s[i - j + 1] == s[i + j];
  //        ++j) {
  //     dp[i + j + 1] = std::min(dp[i + j + 1], dp[i - j + 1] + 1);
  //   }
  //
  // }
  //
  // return dp[n];

  return res;
}

void DecomposeIntoDictionaryWordsWrapper(
    TimedExecutor &executor, const string &domain,
    const unordered_set<string> &dictionary, bool decomposable) {
  vector<string> result = executor.Run(
      [&] { return DecomposeIntoDictionaryWords(domain, dictionary); });
  if (!decomposable) {
    if (!result.empty()) {
      throw TestFailure("domain is not decomposable");
    }
    return;
  }

  if (std::any_of(std::begin(result), std::end(result),
                  [&](const std::string &s) { return !dictionary.count(s); })) {
    throw TestFailure("Result uses words not in dictionary");
  }

  if (std::accumulate(std::begin(result), std::end(result), string()) !=
      domain) {
    throw TestFailure("Result is not composed into domain");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "domain", "dictionary",
                                       "decomposable"};
  return GenericTestMain(args, "is_string_decomposable_into_words.cc",
                         "is_string_decomposable_into_words.tsv",
                         &DecomposeIntoDictionaryWordsWrapper,
                         DefaultComparator{}, param_names);
}
