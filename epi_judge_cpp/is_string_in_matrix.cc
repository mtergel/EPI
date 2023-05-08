#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
using std::unordered_map;
using std::vector;

bool searchWord(int i, int j, int start, vector<vector<bool>> &visited,
                const vector<vector<int>> &grid, const vector<int> &pattern) {

  if (start >= pattern.size()) {
    return true;
  }

  if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() ||
      visited[i][j] || grid[i][j] != pattern[start]) {
    return false;
  }

  visited[i][j] = true;
  bool res = false;

  // check the rest
  res = res || searchWord(i + 1, j, start + 1, visited, grid, pattern);
  res = res || searchWord(i - 1, j, start + 1, visited, grid, pattern);
  res = res || searchWord(i, j + 1, start + 1, visited, grid, pattern);
  res = res || searchWord(i, j - 1, start + 1, visited, grid, pattern);

  return res;
}

bool IsPatternContainedInGrid(const vector<vector<int>> &grid,
                              const vector<int> &pattern) {
  int m = grid.size(), n = grid[0].size();

  // pruning
  if (m * n < pattern.size()) {
    return false;
  }

  unordered_map<int, int> c;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      ++c[grid[i][j]];
    }
  }

  // pruning
  for (const auto &num : pattern) {
    --c[num];
    if (c[num] < 0) {
      return false;
    }
  }

  vector<vector<bool>> visited(m, vector<bool>(n, false));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == pattern[0] &&
          searchWord(i, j, 0, visited, grid, pattern)) {
        return true;
      }
    }
  }

  return false;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"grid", "pattern"};
  return GenericTestMain(args, "is_string_in_matrix.cc",
                         "is_string_in_matrix.tsv", &IsPatternContainedInGrid,
                         DefaultComparator{}, param_names);
}
