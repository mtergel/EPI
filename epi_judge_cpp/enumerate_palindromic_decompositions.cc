#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

bool isPalindrome(int i, int j, const string &s) {
  while (i < j) {
    if (s[i] != s[j]) {
      return false;
    }

    ++i, --j;
  }

  return true;
}

void helper(vector<vector<string>> &res, vector<string> &path, int start,
            const string &text) {

  if (start == text.size()) {
    res.push_back(path);
    return;
  }

  for (int i = start; i < text.size(); ++i) {
    if (isPalindrome(start, i, text)) {
      path.push_back(text.substr(start, i - start + 1));
      helper(res, path, i + 1, text);
      path.pop_back();
    }
  }
}

vector<vector<string>> PalindromeDecompositions(const string &text) {
  vector<vector<string>> res;
  vector<string> path;

  helper(res, path, 0, text);

  return res;
}
bool Comp(vector<vector<string>> expected, vector<vector<string>> result) {
  std::sort(begin(expected), end(expected));
  std::sort(begin(result), end(result));
  return expected == result;
};

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"text"};
  return GenericTestMain(args, "enumerate_palindromic_decompositions.cc",
                         "enumerate_palindromic_decompositions.tsv",
                         &PalindromeDecompositions, &Comp, param_names);
}
