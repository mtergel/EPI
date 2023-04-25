#include <algorithm>
#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// check for conflicts
bool IsValid(vector<int> &curr) {
  int row = curr.size() - 1; // current row for the last placed queen

  // get previous queens
  for (int i = 0; i < row; ++i) {
    int diff = abs(curr[i] - curr[row]);

    // diff == 0        -> same col
    // diff = row - i   -> same diagnol
    if (diff == 0 || diff == row - i) {
      return false;
    }
  }

  return true;
}

void helper(int n, int row, vector<int> *curr, vector<vector<int>> *res) {
  if (row == n) {
    res->emplace_back(*curr);
  } else {

    for (int col = 0; col < n; ++col) {
      curr->emplace_back(col);

      if (IsValid(*curr)) {
        helper(n, row + 1, curr, res);
      }

      curr->pop_back();
    }
  }
}

vector<vector<int>> NQueens(int n) {
  vector<vector<int>> res;
  vector<int> curr;

  helper(n, 0, &curr, &res);

  return res;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens,
                         UnorderedComparator{}, param_names);
}
