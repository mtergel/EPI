#include <climits>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::string;
using std::unordered_map;
using std::vector;

struct Subarray {
  // Represent subarray by starting and ending indices, inclusive.
  int start, end;
};

Subarray FindSmallestSequentiallyCoveringSubset(
    const vector<string>& paragraph, const vector<string>& keywords) {
  unordered_map<string, int> m;
  for (int i = 0; i < keywords.size(); ++i) {
    m[keywords[i]] = i;
  }

  // last occurrence of keyword(idx)
  vector<int> last_idx(keywords.size(), -1);

  // for each keyword(idx)
  // store the length of the shortest subarray
  // ending at the most recent occurrence

  vector<int> shortest_l(keywords.size(), INT_MAX);
  int shortest_dist = INT_MAX;

  Subarray res = Subarray{-1, -1};
  for (int i = 0; i < paragraph.size(); ++i) {
    if (m.find(paragraph[i]) == m.end()) {
      continue;
    }

    int idx = m[paragraph[i]];

    if (idx == 0) {
      // first occurrence, length is 1
      shortest_l[idx] = 1;
    } else if (shortest_l[idx - 1] != INT_MAX) {
      int dist_to_prev_word = i - last_idx[idx - 1];
      shortest_l[idx] = dist_to_prev_word + shortest_l[idx - 1];
    }

    // store occurrence of keyword
    last_idx[idx] = i;

    // on last idx, check for shortest
    if (idx == keywords.size() - 1 && shortest_l[idx] < shortest_dist) {
      shortest_dist = shortest_l[idx];
      res = {i - shortest_l[idx] + 1, i};
    }
  }

  return res;
}
int FindSmallestSequentiallyCoveringSubsetWrapper(
    TimedExecutor& executor, const vector<string>& paragraph,
    const vector<string>& keywords) {
  auto result = executor.Run([&] {
    return FindSmallestSequentiallyCoveringSubset(paragraph, keywords);
  });

  int kw_idx = 0;
  if (result.start < 0) {
    throw TestFailure("Subarray start index is negative");
  }
  int para_idx = result.start;

  while (kw_idx < keywords.size()) {
    if (para_idx >= paragraph.size()) {
      throw TestFailure("Not all keywords are in the generated subarray");
    }
    if (para_idx >= paragraph.size()) {
      throw TestFailure("Subarray end index exceeds array size");
    }
    if (paragraph[para_idx] == keywords[kw_idx]) {
      kw_idx++;
    }
    para_idx++;
  }
  return result.end - result.start + 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_all_values.cc",
                         "smallest_subarray_covering_all_values.tsv",
                         &FindSmallestSequentiallyCoveringSubsetWrapper,
                         DefaultComparator{}, param_names);
}
