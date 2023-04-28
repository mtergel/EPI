#include <algorithm>
#include <cmath>
#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::begin;
using std::end;
using std::vector;

const int EMPTY_ENTRY = 0;

bool IsValidToAdd(vector<vector<int>> &grid, int i, int j, int val) {
  // check row
  for (int k = 0; k < grid.size(); ++k) {
    if (val == grid[k][j]) {
      return false;
    }
  }

  // check col
  for (int k = 0; k < grid[i].size(); ++k) {
    if (val == grid[i][k]) {
      return false;
    }
  }

  // check sub grid
  int subSize = sqrt(grid.size());
  int I = i / subSize, J = j / subSize;

  for (int a = 0; a < subSize; ++a) {
    for (int b = 0; b < subSize; ++b) {
      if (val == grid[subSize * I + a][subSize * J + b]) {
        return false;
      }
    }
  }

  return true;
}

bool helper(int i, int j, vector<vector<int>> *grid) {
  // check each entry

  if (i == grid->size()) {
    // at end of row
    // prepare go to first column of next row
    i = 0;

    // if at the last row
    if (++j == grid[i].size()) {
      // made it here without returning false
      // so sudoku solved!
      return true;
    }
  }

  // skip filled
  if ((*grid)[i][j] != EMPTY_ENTRY) {
    return helper(i + 1, j, grid);
  }

  // start filling the entry with 1->9
  for (int val = 1; val <= grid->size(); ++val) {
    // its quicker to check, before adding then checking
    if (IsValidToAdd(*grid, i, j, val)) {
      (*grid)[i][j] = val;

      // check sudoku with current val
      if (helper(i + 1, j, grid)) {
        return true;
      }
    }
  }

  // can't find a valid value for entry
  (*grid)[i][j] = EMPTY_ENTRY;
  return false;
}

bool SolveSudoku(vector<vector<int>> *partial_assignment) {
  return helper(0, 0, partial_assignment);
}
vector<int> GatherColumn(const vector<vector<int>> &data, size_t i) {
  vector<int> result;
  for (auto &row : data) {
    result.push_back(row[i]);
  }
  return result;
}

vector<int> GatherSquareBlock(const vector<vector<int>> &data,
                              size_t block_size, size_t n) {
  vector<int> result;
  size_t block_x = n % block_size;
  size_t block_y = n / block_size;
  for (size_t i = block_x * block_size; i < (block_x + 1) * block_size; i++) {
    for (size_t j = block_y * block_size; j < (block_y + 1) * block_size; j++) {
      result.push_back(data[i][j]);
    }
  }

  return result;
}

void AssertUniqueSeq(const vector<int> &seq) {
  vector<bool> seen(seq.size(), false);
  for (auto &x : seq) {
    if (x == 0) {
      throw TestFailure("Cell left uninitialized");
    }
    if (x < 0 || x > seq.size()) {
      throw TestFailure("Cell value out of range");
    }
    if (seen[x - 1]) {
      throw TestFailure("Duplicate value in section");
    }
    seen[x - 1] = true;
  }
}

void SolveSudokuWrapper(TimedExecutor &executor,
                        const vector<vector<int>> &partial_assignment) {
  vector<vector<int>> solved = partial_assignment;

  executor.Run([&] { SolveSudoku(&solved); });

  if (!std::equal(begin(partial_assignment), end(partial_assignment),
                  begin(solved), end(solved), [](auto br, auto cr) {
                    return std::equal(begin(br), end(br), begin(cr), end(cr),
                                      [](int bcell, int ccell) {
                                        return bcell == 0 || bcell == ccell;
                                      });
                  }))
    throw TestFailure("Initial cell assignment has been changed");

  auto block_size = static_cast<size_t>(sqrt(solved.size()));

  for (size_t i = 0; i < solved.size(); i++) {
    AssertUniqueSeq(solved[i]);
    AssertUniqueSeq(GatherColumn(solved, i));
    AssertUniqueSeq(GatherSquareBlock(solved, block_size, i));
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "partial_assignment"};
  return GenericTestMain(args, "sudoku_solve.cc", "sudoku_solve.tsv",
                         &SolveSudokuWrapper, DefaultComparator{}, param_names);
}
