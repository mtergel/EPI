#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::pair;
using std::vector;

struct MinMax {
  int smallest, largest;
};

MinMax FindMinMax(const vector<int>& A) {
  // TODO - you fill in here.
  // less than 2(n - 1)
  if (A.size() == 1) {
    return {A[0], A[0]};
  }

  pair<int, int> res = std::minmax(A[0], A[1]);
  for (int i = 2; i + 1 < A.size(); i += 2) {
    pair<int, int> local = std::minmax(A[i], A[i + 1]);
    res = {std::min(res.first, local.first),
           std::max(res.second, local.second)};
  }

  if (A.size() % 2) {
    res = {std::min(res.first, A.back()), std::max(res.second, A.back())};
  };

  return {res.first, res.second};
}
namespace test_framework {
template <>
struct SerializationTrait<MinMax> : UserSerTrait<MinMax, int, int> {};
}  // namespace test_framework

bool operator==(const MinMax& lhs, const MinMax& rhs) {
  return std::tie(lhs.smallest, lhs.largest) ==
         std::tie(rhs.smallest, rhs.largest);
}

std::ostream& operator<<(std::ostream& out, const MinMax& x) {
  return out << "min: " << x.smallest << ", max: " << x.largest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_for_min_max_in_array.cc",
                         "search_for_min_max_in_array.tsv", &FindMinMax,
                         DefaultComparator{}, param_names);
}
