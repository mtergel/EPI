#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

struct Subarray {
  int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(
    const vector<string> &paragraph, const unordered_set<string> &keywords) {
  Subarray res = Subarray{-1, -1};
  std::unordered_map<string, int> m;

  for (const string &k : keywords) {
    ++m[k];
  }

  int total = keywords.size();
  for (int l = 0, r = 0; r < paragraph.size(); ++r) {
    if (keywords.count(paragraph[r]) && --m[paragraph[r]] >= 0) {
      --total;
    }

    // keep advancing left untill m does not
    // contain all keywords
    while (total == 0) {
      if ((res.start == -1 && res.end == -1) || r - l < res.end - res.start) {
        res = {l, r};
      }

      if (keywords.count(paragraph[l]) && ++m[paragraph[l]] > 0) {
        ++total;
      }

      ++l;
    }
  }

  return res;
}
int FindSmallestSubarrayCoveringSetWrapper(
    TimedExecutor &executor, const vector<string> &paragraph,
    const unordered_set<string> &keywords) {
  unordered_set<string> copy = keywords;

  auto result = executor.Run(
      [&] { return FindSmallestSubarrayCoveringSet(paragraph, keywords); });

  if (result.start < 0 || result.start >= paragraph.size() || result.end < 0 ||
      result.end >= paragraph.size() || result.start > result.end) {
    throw TestFailure("Index out of range");
  }

  for (int i = result.start; i <= result.end; i++) {
    copy.erase(paragraph[i]);
  }

  if (!copy.empty()) {
    throw TestFailure("Not all keywords are in the range");
  }

  return result.end - result.start + 1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_set.cc",
                         "smallest_subarray_covering_set.tsv",
                         &FindSmallestSubarrayCoveringSetWrapper,
                         DefaultComparator{}, param_names);
}
