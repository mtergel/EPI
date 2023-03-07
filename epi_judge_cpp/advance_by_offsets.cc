#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"
using std::max;
using std::vector;

bool CanReachEnd(const vector<int>& max_advance_steps) {
  // moving goal post method
  // int goal = max_advance_steps.size() - 1;
  // for (int i = max_advance_steps.size() - 2; i >= 0; --i) {
  //   if (max_advance_steps[i] + i >= goal) {
  //     goal = i;
  //   }
  // }
  // return goal == 0;

  // greedy
  int n = max_advance_steps.size();
  int curFar = 0;
  for (int i = 0; i <= curFar && curFar < n - 1; ++i) {
    curFar = max(curFar, max_advance_steps[i] + i);
    // minimum steps counter
    // if (i == curEnd) {
    //   step++;
    //   curEnd = curFar;
    // }
  }

  return curFar >= n - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
