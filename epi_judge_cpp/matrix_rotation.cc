#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
  vector<vector<int>>& square_matrix = *square_matrix_ptr;
  const int matrix_size = square_matrix.size() - 1;

  for (int i = 0; i < (square_matrix.size() + 1) / 2; ++i) {
    for (int j = 0; j < square_matrix.size() / 2; ++j) {
      int bl = square_matrix[matrix_size - j][i];
      int br = square_matrix[matrix_size - i][matrix_size - j];
      int tr = square_matrix[j][matrix_size - i];
      int tl = square_matrix[i][j];

      square_matrix[i][j] = bl;
      square_matrix[matrix_size - j][i] = br;
      square_matrix[matrix_size - i][matrix_size - j] = tr;
      square_matrix[j][matrix_size - i] = tl;
    }
  }
  return;
}
vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> square_matrix) {
  RotateMatrix(&square_matrix);
  return square_matrix;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "matrix_rotation.cc", "matrix_rotation.tsv",
                         &RotateMatrixWrapper, DefaultComparator{},
                         param_names);
}
