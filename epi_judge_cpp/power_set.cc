#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void helper(vector<vector<int>> &res, int start, vector<int> &path,
            const vector<int> &input_set) {

  if (start == input_set.size()) {
    res.push_back(path);
    return;
  }

  path.push_back(input_set[start]);
  helper(res, start + 1, path, input_set);
  path.pop_back();
  helper(res, start + 1, path, input_set);
}

vector<vector<int>> GeneratePowerSet(const vector<int> &input_set) {
  vector<vector<int>> res;
  vector<int> path;
  helper(res, 0, path, input_set);

  return res;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input_set"};
  return GenericTestMain(args, "power_set.cc", "power_set.tsv",
                         &GeneratePowerSet, UnorderedComparator{}, param_names);
}
