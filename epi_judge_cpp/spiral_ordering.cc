#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  vector<int> res;
  int l = 0, t = 0, r = square_matrix.size() - 1, b = square_matrix.size() - 1;

  while (t <= b && l <= r) {
    for (int i = l; i <= r; ++i) {
      res.push_back(square_matrix[t][i]);
    }
    ++t;

    for (int j = t; j <= b; ++j) {
      res.push_back(square_matrix[j][r]);
    }
    --r;

    if (t <= b) {
      for (int i = r; i >= l; --i) {
        res.push_back(square_matrix[b][i]);
      }
    }
    --b;

    if (l <= r) {
      for (int j = b; j >= t; --j) {
        res.push_back(square_matrix[j][l]);
      }
    }
    ++l;
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
