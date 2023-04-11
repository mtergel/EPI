#include <algorithm>
#include <climits>
#include <string>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;
using std::vector;

int FindNearestRepetition(const vector<string>& paragraph) {
  unordered_map<string, int> m;
  int res = INT_MAX;

  for (int i = 0; i < paragraph.size(); ++i) {
    auto latest_word = m.find(paragraph[i]);
    if (latest_word != m.end()) {
      res = std::min(res, i - latest_word->second);
    }

    m[paragraph[i]] = i;
  }

  return res == INT_MAX ? -1 : res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
