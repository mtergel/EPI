
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int helper(const unique_ptr<BinaryTreeNode<int>>& tree, int sum) {
  if (tree == nullptr) {
    return 0;
  }

  sum = sum * 2 + tree->data;
  if (tree->left == nullptr && tree->right == nullptr) {
    return sum;
  }

  return helper(tree->left, sum) + helper(tree->right, sum);
}
int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return helper(tree, 0);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
