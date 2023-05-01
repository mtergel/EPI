#include "test_framework/generic_test.h"
int Fibonacci(int n) {
  if (n <= 1) {
    return n;
  }

  int prev = 0, curr = 1;
  for (int i = 2; i <= n; ++i) {
      int temp = curr + prev;
      prev = curr;
      curr = temp;
  }

  return curr;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "fibonacci.cc", "fibonacci.tsv", &Fibonacci,
                         DefaultComparator{}, param_names);
}
