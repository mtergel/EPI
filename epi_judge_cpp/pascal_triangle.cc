#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<vector<int>> GeneratePascalTriangle(int num_rows) {
  vector<vector<int>> res;
  for (int i = 0; i < num_rows; ++i) {
    vector<int> row;
    for (int j = 0; j <= i; ++j) {
      row.emplace_back(0 < j && j < i ? res.back()[j - 1] + res.back()[j] : 1);
    }
    res.emplace_back(row);
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_rows"};
  return GenericTestMain(args, "pascal_triangle.cc", "pascal_triangle.tsv",
                         &GeneratePascalTriangle, DefaultComparator{},
                         param_names);
}
