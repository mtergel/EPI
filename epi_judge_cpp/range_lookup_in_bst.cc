#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::unique_ptr;
using std::vector;

struct Interval {
  int left, right;
};

void helper(const unique_ptr<BstNode<int>> &root, const Interval &interval,
            vector<int> *res) {
  if (root == nullptr)
    return;

  if (interval.left <= root->data && root->data <= interval.right) {
    helper(root->left, interval, res);
    res->emplace_back(root->data);
    helper(root->right, interval, res);
  } else if (interval.left > root->data) {
    helper(root->right, interval, res);
  } else {
    helper(root->left, interval, res);
  }
}

vector<int> RangeLookupInBST(const unique_ptr<BstNode<int>> &tree,
                             const Interval &interval) {
  vector<int> res;
  helper(tree, interval, &res);

  return res;
}
void RangeLookupInBSTHelper(const unique_ptr<BstNode<int>> &tree,
                            const Interval &interval, vector<int> *result) {}

namespace test_framework {
template <>
struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string &arg_name) {
    return {FmtStr("length({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Interval &x) {
    return {x.right - x.left};
  }
};
} // namespace test_framework

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "interval"};
  return GenericTestMain(args, "range_lookup_in_bst.cc",
                         "range_lookup_in_bst.tsv", &RangeLookupInBST,
                         DefaultComparator{}, param_names);
}
