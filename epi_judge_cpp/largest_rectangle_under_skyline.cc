#include <climits>
#include <stack>
#include <utility>
#include <vector>

#include "test_framework/generic_test.h"
using std::max;
using std::pair;
using std::stack;
using std::vector;

int CalculateLargestRectangle(const vector<int> &heights) {
  if (heights.empty())
    return 0;

  stack<pair<int, int>> s; // height, idx
  int res = 0;

  for (int i = 0; i < heights.size(); ++i) {
    int lastIdx = i;
    while (!s.empty() && s.top().first > heights[i]) {
      int h = s.top().first;
      int idx = s.top().second;

      s.pop();
      res = max(res, h * (i - idx));

      lastIdx = idx;
    }

    // this height[i] didnt start at i, it started at lastIdx
    s.push({heights[i], lastIdx});
  }

  while (!s.empty()) {
    int dist = heights.size() - s.top().second;
    int h = s.top().first;

    s.pop();

    res = max(res, h * dist);
  }

  return res;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"heights"};
  return GenericTestMain(args, "largest_rectangle_under_skyline.cc",
                         "largest_rectangle_under_skyline.tsv",
                         &CalculateLargestRectangle, DefaultComparator{},
                         param_names);
}
