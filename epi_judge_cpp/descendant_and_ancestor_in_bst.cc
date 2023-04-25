#include <memory>

#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

bool SearchTarget(const unique_ptr<BstNode<int>> &from,
                  const unique_ptr<BstNode<int>> &target) {
  auto *iter = from.get();
  while (iter && iter != target.get()) {
    iter = iter->data > target->data ? iter->left.get() : iter->right.get();
  }

  return iter == target.get();
}

bool PairIncludesAncestorAndDescendantOfM(
    const unique_ptr<BstNode<int>> &node0,
    const unique_ptr<BstNode<int>> &node1,
    const unique_ptr<BstNode<int>> &middle) {

  auto n0 = node0.get();
  auto n1 = node1.get();

  while (n0 != node1.get() && n1 != node0.get() && n0 != middle.get() &&
         n1 != middle.get() && (n0 || n1)) {
    if (n0) {
      n0 = n0->data > middle->data ? n0->left.get() : n0->right.get();
    }

    if (n1) {
      n1 = n1->data > middle->data ? n1->left.get() : n1->right.get();
    }
  }

  if ((n0 != middle.get() && n1 != middle.get()) || n0 == node1.get() ||
      n1 == node0.get()) {
    return false;
  }

  return n0 == middle.get() ? SearchTarget(middle, node1)
                            : SearchTarget(middle, node0);
}

bool PairIncludesAncestorAndDescendantOfMWrapper(
    TimedExecutor &executor, const unique_ptr<BstNode<int>> &tree,
    int possible_anc_or_desc_0, int possible_anc_or_desc_1, int middle) {
  auto &candidate0 = MustFindNode(tree, possible_anc_or_desc_0);
  auto &candidate1 = MustFindNode(tree, possible_anc_or_desc_1);
  auto &middle_node = MustFindNode(tree, middle);
  return executor.Run([&] {
    return PairIncludesAncestorAndDescendantOfM(candidate0, candidate1,
                                                middle_node);
  });
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree",
                                       "possible_anc_or_desc_0",
                                       "possible_anc_or_desc_1", "middle"};
  return GenericTestMain(args, "descendant_and_ancestor_in_bst.cc",
                         "descendant_and_ancestor_in_bst.tsv",
                         &PairIncludesAncestorAndDescendantOfMWrapper,
                         DefaultComparator{}, param_names);
}
