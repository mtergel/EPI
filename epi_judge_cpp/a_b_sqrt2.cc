#include <set>
#include <vector>

#include "test_framework/generic_test.h"
using std::function;
using std::set;
using std::vector;

struct ABSqrt2 {

  ABSqrt2(int a, int b) : a(a), b(b), val(a + b * sqrt(2)) {}

  int a, b;
  double val;
};

vector<double> GenerateFirstKABSqrt2(int k) {

  set<ABSqrt2, function<bool(ABSqrt2, ABSqrt2)>> candidates(
      {{0, 0}},
      [](const ABSqrt2 &a, const ABSqrt2 &b) { return a.val < b.val; });

  vector<double> res;
  while (res.size() < k) {
    auto next = candidates.cbegin();
    res.emplace_back(next->val);

    candidates.emplace(next->a + 1, next->b);
    candidates.emplace(next->a, next->b + 1);

    candidates.erase(next);
  }

  return res;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "a_b_sqrt2.cc", "a_b_sqrt2.tsv",
                         &GenerateFirstKABSqrt2, DefaultComparator{},
                         param_names);
}
