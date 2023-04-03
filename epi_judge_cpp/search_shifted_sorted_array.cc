#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchSmallest(const vector<int>& A) {
  if (A.front() < A.back()) {
    return 0;
  }

  int l = 0, r = A.size() - 1;
  while (l < r) {
    int mid = l + (r - l) / 2;

    if (A[mid] > A[r]) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }

  return l;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
