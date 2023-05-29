#include <climits>
#include <map>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::sort;
using std::vector;

struct Interval {
  int left, right;
};

int FindMinimumVisits(vector<Interval> intervals) {
  if (intervals.empty()) {
    return {};
  }

  sort(intervals.begin(), intervals.end(),
       [](const Interval &a, const Interval &b) { return a.right < b.right; });

  int curr_ending = INT_MIN;
  int res = 0;

  for (const Interval &i : intervals) {
    // previous interval ended must check now
    if (i.left > curr_ending) {
      curr_ending = i.right;
      ++res;
    }
  }

  return res;
}
namespace test_framework {
template <>
struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int> {};
} // namespace test_framework

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"intervals"};
  return GenericTestMain(args, "minimum_points_covering_intervals.cc",
                         "minimum_points_covering_intervals.tsv",
                         &FindMinimumVisits, DefaultComparator{}, param_names);
}
