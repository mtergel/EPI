#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void helper(vector<vector<int>> &res, vector<int> &path, int start, int n,
            int k) {

  if (path.size() == k) {
    res.push_back(path);
    return;
  }

  for (int i = start; i <= n; ++i) {
    path.push_back(i);
    helper(res, path, i + 1, n, k);
    path.pop_back();
  }
}

vector<vector<int>> Combinations(int n, int k) {
  vector<vector<int>> res;
  vector<int> path;

  helper(res, path, 1, n, k);
  return res;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(args, "combinations.cc", "combinations.tsv",
                         &Combinations, UnorderedComparator{}, param_names);
}
