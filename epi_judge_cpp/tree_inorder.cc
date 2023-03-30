#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::stack;
using std::unique_ptr;
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> res;
  stack<const BinaryTreeNode<int>*> s;

  const auto* curr = tree.get();

  while (curr || !s.empty()) {
    // go left
    while (curr) {
      s.push(curr);
      curr = curr->left.get();
    }

    // go right
    curr = s.top();
    s.pop();

    res.emplace_back(curr->data);
    curr = curr->right.get();
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
