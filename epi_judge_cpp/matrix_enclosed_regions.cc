#include <queue>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::pair;
using std::queue;
using std::string;
using std::vector;

void FillSurroundedRegions(vector<vector<char>> *board_ptr) {
  vector<vector<char>> &board = *board_ptr;
  int m = board.size();
  if (m == 0)
    return;

  int n = board[0].size();

  vector<vector<bool>> visited(m, vector<bool>(n, false));
  queue<pair<int, int>> q;

  for (int j = 0; j < n; ++j) {
    if (board[0][j] == 'W') {
      q.push({0, j});
    }

    if (board[m - 1][j] == 'W') {
      q.push({m - 1, j});
    }
  }

  for (int i = 0; i < m; ++i) {
    if (board[i][0] == 'W') {
      q.push({i, 0});
    }

    if (board[i][n - 1] == 'W') {
      q.push({i, n - 1});
    }
  }

  int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  while (!q.empty()) {
    int i = q.front().first;
    int j = q.front().second;
    q.pop();

    visited[i][j] = true;

    for (int k = 0; k < 4; ++k) {
      int ni = i + dirs[k][0];
      int nj = j + dirs[k][1];

      if (ni < 0 || nj < 0 || ni >= m || nj >= n || board[ni][nj] == 'B' ||
          visited[ni][nj]) {
        continue;
      }

      q.push({ni, nj});
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (board[i][j] == 'W' && !visited[i][j]) {
        board[i][j] = 'B';
      }
    }
  }

  return;
}
vector<vector<string>>
FillSurroundedRegionsWrapper(TimedExecutor &executor,
                             vector<vector<string>> board) {
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++) {
    for (const string &s : board[i]) {
      if (s.size() != 1) {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  executor.Run([&] { FillSurroundedRegions(&char_vector); });

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++) {
    for (char c : char_vector[i]) {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "board"};
  return GenericTestMain(
      args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
      &FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
