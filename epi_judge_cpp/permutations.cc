#include <vector>

#include "test_framework/generic_test.h"
using std::swap;
using std::vector;

void helper(vector<vector<int>> &res, int n, vector<int> &A) {

  if (n == A.size() - 1) {
    res.push_back(A);
  } else {
    for (int i = n; i < A.size(); ++i) {
      swap(A[i], A[n]);
      helper(res, n + 1, A);
      swap(A[i], A[n]);
    }
  }
}

vector<vector<int>> Permutations(vector<int> A) {
  vector<vector<int>> res;

  helper(res, 0, A);

  return res;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "permutations.cc", "permutations.tsv",
                         &Permutations, UnorderedComparator{}, param_names);
}
