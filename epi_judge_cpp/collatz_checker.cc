#include <string>
#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
using std::overflow_error;
using std::vector;

bool TestCollatzConjecture(int n) {
  std::unordered_set<long> nums;
  for (int i = 3; i <= n; i += 2) {
    std::unordered_set<long> seq;
    long test_i = i;

    while (test_i >= i) {
      if (!seq.emplace(test_i).second) {
        // loop
        return false;
      }

      if (test_i % 2) {
        if (!nums.emplace(test_i).second) {
          break;
        }

        long next_test_i = 3 * test_i + 1;
        if (next_test_i <= test_i) {
          throw overflow_error("Collatz sequence overflow for " +
                               std::to_string(i));
        }

        test_i = next_test_i;
      } else {
        test_i /= 2;
      }
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "collatz_checker.cc", "collatz_checker.tsv",
                         &TestCollatzConjecture, DefaultComparator{},
                         param_names);
}
