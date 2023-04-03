#include <limits>

#include "test_framework/generic_test.h"

typedef enum { SMALLER, EQUAL, LARGER } Ordering;
Ordering Compare(double a, double b) {
  // normalization for precision problem
  double diff = (a - b) / b;
  return diff < -std::numeric_limits<double>::epsilon()  ? SMALLER
         : diff > std::numeric_limits<double>::epsilon() ? LARGER
                                                         : EQUAL;
}

double SquareRoot(double x) {
  double l, r;
  if (x < 1.0) {
    l = x, r = 1.0;
  } else {
    l = 1.0, r = x;
  }

  while (Compare(l, r) == SMALLER) {
    double mid = l + 0.5 * (r - l);
    double mid_s = mid * mid;

    if (Compare(mid_s, x) == EQUAL) {
      return mid;
    } else if (Compare(mid_s, x) == LARGER) {
      r = mid;
    } else {
      l = mid;
    }
  }

  return l;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
