#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& board) {
  const int count = 9;

  bool row[count][count] = {false};
  bool col[count][count] = {false};
  bool sub[count][count] = {false};

  for (int r = 0; r < count; ++r) {
    for (int c = 0; c < count; ++c) {
      if (board[r][c] == 0) {
        continue;
      }

      int idx = board[r][c] - 1;
      int area = (r / 3) * 3 + (c / 3);
      if (row[r][idx] || col[c][idx] || sub[area][idx]) {
        return false;
      }

      row[r][idx] = true;
      col[c][idx] = true;
      sub[area][idx] = true;
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
