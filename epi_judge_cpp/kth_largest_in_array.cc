#include <vector>

#include "test_framework/generic_test.h"
using std::swap;
using std::vector;

int quickSelect(vector<int>& nums, int k, int l, int r) {
  int pivot = nums[r];
  int j = l;

  for (int i = l; i < r; ++i) {
    if (nums[i] <= pivot) {
      swap(nums[i], nums[j++]);
    }
  }

  swap(nums[j], nums[r]);

  // nums in j is in sorted place now
  if (k < j) {
    return quickSelect(nums, k, l, j - 1);
  } else if (k > j) {
    return quickSelect(nums, k, j + 1, r);
  } else {
    return nums[j];
  }
}

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;
  int idx = A.size() - k;
  return quickSelect(A, idx, 0, A.size() - 1);
}
int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
