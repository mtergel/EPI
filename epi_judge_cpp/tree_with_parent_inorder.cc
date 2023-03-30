#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  BinaryTreeNode<int>*prev = nullptr, *curr = tree.get();
  vector<int> res;

  while (curr) {
    BinaryTreeNode<int>* next;
    if (curr->parent == prev) {
      // we came down to curr from prev
      if (curr->left) {
        // traverse to left
        next = curr->left.get();
      } else {
        // no more left
        res.emplace_back(curr->data);
        // go right if not empty
        // otherwise go up
        next = curr->right ? curr->right.get() : curr->parent;
      }
    } else if (curr->left.get() == prev) {
      // we came up to curr from its left child
      res.emplace_back(curr->data);
      // done with left subtree
      next = curr->right ? curr->right.get() : curr->parent;
    } else {
      // we came up to curr from its right child
      next = curr->parent;
    }

    prev = curr;
    curr = next;
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
