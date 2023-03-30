#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool helper(const unique_ptr<BinaryTreeNode<int>>& n1,
            const unique_ptr<BinaryTreeNode<int>>& n2) {
  if (n1 == nullptr && n2 == nullptr) {
    return true;
  } else if (n1 && n2) {
    return n1->data == n2->data && helper(n1->left, n2->right) &&
           helper(n1->right, n2->left);

  } else {
    return false;
  }
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (tree == nullptr) {
    return true;
  }

  return helper(tree->left, tree->right);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
