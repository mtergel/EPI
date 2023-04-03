#include "test_framework/generic_test.h"

int SquareRoot(int k) {
  int l = 0, r = k;
  while (l <= r) {
    long mid = l + (r - l) / 2;
    long mid_s = mid * mid;

    if (mid_s == k) {
      return mid;
    } else if (mid_s > k) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return l - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
