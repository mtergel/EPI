#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"

BinaryTreeNode<int>* FindSuccessor(
    const unique_ptr<BinaryTreeNode<int>>& node) {
  if (node == nullptr) {
    return nullptr;
  }

  auto* curr = node.get();
  if (node->right) {
    curr = curr->right.get();
    while (curr->left) {
      curr = curr->left.get();
    }

    return curr;
  }

  // find closest ancestor
  // whose left subtree contains curr
  while (curr->parent && curr->parent->right.get() == curr) {
    curr = curr->parent;
  }

  return curr->parent;
}
int FindSuccessorWrapper(const unique_ptr<BinaryTreeNode<int>>& tree,
                         int node_idx) {
  auto result = FindSuccessor(MustFindNode(tree, node_idx));
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "node_idx"};
  return GenericTestMain(args, "successor_in_tree.cc", "successor_in_tree.tsv",
                         &FindSuccessorWrapper, DefaultComparator{},
                         param_names);
}
