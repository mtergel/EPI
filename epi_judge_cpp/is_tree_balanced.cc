#include <algorithm>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

using std::abs;
using std::max;

// gets tree's height
int helper(const unique_ptr<BinaryTreeNode<int>>& node) {
  if (node == nullptr) {
    return 0;
  }

  int leftH = helper(node->left);
  if (leftH == -1) {
    return -1;
  }

  int rightH = helper(node->right);
  if (rightH == -1) {
    return -1;
  }

  if (abs(leftH - rightH) > 1) {
    return -1;
  }
  return max(leftH, rightH) + 1;
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return helper(tree) != -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
