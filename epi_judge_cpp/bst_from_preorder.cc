#include <algorithm>
#include <climits>
#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

unique_ptr<BstNode<int>> helper(const vector<int> &preorder_sequence, int bound,
                                int *root_idx_pointer) {
  int &root_idx = *root_idx_pointer;
  if (root_idx == preorder_sequence.size() ||
      preorder_sequence[root_idx] > bound) {
    return nullptr;
  }

  auto root = std::make_unique<BstNode<int>>(
      BstNode<int>{preorder_sequence[root_idx++]});

  root->left = helper(preorder_sequence, root->data, root_idx_pointer);
  root->right = helper(preorder_sequence, bound, root_idx_pointer);

  return root;
}

unique_ptr<BstNode<int>>
RebuildBSTFromPreorder(const vector<int> &preorder_sequence) {
  // [3,2,1,5,4,6] this should be bst
  // so parent, left subtree, right subtree

  int root_idx = 0;
  return helper(preorder_sequence, INT_MAX, &root_idx);
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder_sequence"};
  return GenericTestMain(args, "bst_from_preorder.cc", "bst_from_preorder.tsv",
                         &RebuildBSTFromPreorder, DefaultComparator{},
                         param_names);
}
