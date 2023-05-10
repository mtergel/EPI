#include <vector>

#include "test_framework/generic_test.h"
using std::sort;
using std::vector;

bool HasTwoSum(const vector<int> &A, int i, int j, int t) {
  while (i <= j) {
    int sum = A[i] + A[j];
    if (sum == t) {
      return true;
    } else if (sum < t) {
      ++i;
    } else {
      --j;
    }
  }

  return false;
}

bool HasThreeSum(vector<int> A, int t) {
  sort(A.begin(), A.end());
  for (int i = 0; i < A.size(); ++i) {
    if (i > 0 && A[i - 1] == A[i]) {
      continue;
    }

    int target = t - A[i];
    if (HasTwoSum(A, i, A.size() - 1, target)) {
      return true;
    }
  }

  return false;

  // Variant: k_sum, recursive call untill k = 2
  // Variant: |T - (A[p] + A[q] + A[r])|, just maintain sum, check every
  // combination
  //
  // Variant: (A[p] + A[q] + A[r]) <= T, just maintain sum, check every
  // combination
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}
