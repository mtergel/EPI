#include <memory>
#include <unordered_map>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::make_unique;
using std::unordered_map;
using std::vector;

unique_ptr<BinaryTreeNode<int>> helper(const vector<int>& preorder,
                                       size_t preorder_start,
                                       size_t preorder_end,
                                       size_t inorder_start, size_t inorder_end,
                                       const unordered_map<int, size_t>& m) {
  if (preorder_end <= preorder_start || inorder_end <= inorder_start) {
    return nullptr;
  }

  size_t root_idx = m.at(preorder[preorder_start]);
  size_t left_size = root_idx - inorder_start;

  return make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
      preorder[preorder_start],
      helper(preorder, preorder_start + 1, preorder_start + 1 + left_size,
             inorder_start, root_idx, m),
      helper(preorder, preorder_start + 1 + left_size, preorder_end,
             root_idx + 1, inorder_end, m)});
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
  unordered_map<int, size_t> m;
  for (size_t i = 0; i < inorder.size(); ++i) {
    m.emplace(inorder[i], i);
  }

  return helper(preorder, 0, preorder.size(), 0, inorder.size(), m);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
