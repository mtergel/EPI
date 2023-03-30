#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::stack;
using std::vector;

vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> res;
  stack<const BinaryTreeNode<int>*> stk;
  stk.emplace(tree.get());

  while (!stk.empty()) {
    auto curr = stk.top();
    stk.pop();

    if (curr != nullptr) {
      res.emplace_back(curr->data);
      stk.emplace(curr->right.get());
      stk.emplace(curr->left.get());
    }
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_preorder.cc", "tree_preorder.tsv",
                         &PreorderTraversal, DefaultComparator{}, param_names);
}
