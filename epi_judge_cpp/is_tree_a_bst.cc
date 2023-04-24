#include <climits>
#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool helper(const unique_ptr<BinaryTreeNode<int>>& node, int minval,
            int maxval) {
  if (node == nullptr) return true;

  if (node->data < minval || node->data > maxval) {
    return false;
  }

  return helper(node->left, minval, node->data) &&
         helper(node->right, node->data, maxval);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return helper(tree, INT_MIN, INT_MAX);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
