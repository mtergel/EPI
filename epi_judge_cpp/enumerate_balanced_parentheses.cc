#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

void helper(vector<string> &res, string path, int open, int close, int n) {

  if (open == n && close == n) {
    res.push_back(path);
    return;
  }

  if (open < n) {
    helper(res, path + "(", open + 1, close, n);
  }

  if (close < open) {
    helper(res, path + ")", open, close + 1, n);
  }

  // can't close bracket unless we open it first
}

vector<string> GenerateBalancedParentheses(int num_pairs) {
  vector<string> res;
  helper(res, "", 0, 0, num_pairs);

  return res;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_pairs"};
  return GenericTestMain(args, "enumerate_balanced_parentheses.cc",
                         "enumerate_balanced_parentheses.tsv",
                         &GenerateBalancedParentheses, UnorderedComparator{},
                         param_names);
}
