#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::swap;

int GetDepth(const BinaryTreeNode<int>* node) {
  if (node == nullptr) {
    return 0;
  }

  int res = 0;

  while (node->parent) {
    ++res, node = node->parent;
  }

  return res;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  int p_height = GetDepth(node0.get());
  int q_height = GetDepth(node1.get());

  auto *iter_p = node0.get(), *iter_q = node1.get();
  if (q_height > p_height) {
    swap(iter_p, iter_q);
  }

  int height_diff = abs(p_height - q_height);
  while (height_diff--) {
    iter_p = iter_p->parent;
  }

  while (iter_p != iter_q) {
    iter_p = iter_p->parent;
    iter_q = iter_q->parent;
  }

  return iter_p;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
