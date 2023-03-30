#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool helper(const unique_ptr<BinaryTreeNode<int>>& tree, int sum,
            int remaining_weight) {
  if (tree == nullptr) {
    return false;
  }

  sum += tree->data;

  if (tree->left == nullptr && tree->right == nullptr) {
    return sum == remaining_weight;
  }

  return helper(tree->left, sum, remaining_weight) ||
         helper(tree->right, sum, remaining_weight);
}
bool HasPathSum(const unique_ptr<BinaryTreeNode<int>>& tree,
                int remaining_weight) {
  return helper(tree, 0, remaining_weight);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "remaining_weight"};
  return GenericTestMain(args, "path_sum.cc", "path_sum.tsv", &HasPathSum,
                         DefaultComparator{}, param_names);
}
