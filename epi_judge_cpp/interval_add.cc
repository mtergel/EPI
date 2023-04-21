#include <algorithm>
#include <vector>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Interval {
  int left, right;
};

vector<Interval> AddInterval(const vector<Interval>& disjoint_intervals,
                             Interval new_interval) {
  vector<Interval> res;
  int i = 0, n = disjoint_intervals.size();

  // add untill merge
  while (i < n && disjoint_intervals[i].right < new_interval.left) {
    res.push_back(disjoint_intervals[i++]);
  }

  // merge
  while (i < n && new_interval.right >= disjoint_intervals[i].left) {
    new_interval.left = std::min(disjoint_intervals[i].left, new_interval.left);
    new_interval.right =
        std::max(disjoint_intervals[i].right, new_interval.right);
    ++i;
  }

  res.push_back(new_interval);

  // add rest
  while (i < n) {
    res.push_back(disjoint_intervals[i++]);
  }

  return res;
}
namespace test_framework {
template <>
struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("length({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Interval& x) {
    return {x.right - x.left};
  }
};
}  // namespace test_framework
bool operator==(const Interval& a, const Interval& b) {
  return a.left == b.left && a.right == b.right;
}

std::ostream& operator<<(std::ostream& out, const Interval& i) {
  return PrintTo(out, std::make_tuple(i.left, i.right));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"disjoint_intervals", "new_interval"};
  return GenericTestMain(args, "interval_add.cc", "interval_add.tsv",
                         &AddInterval, DefaultComparator{}, param_names);
}
