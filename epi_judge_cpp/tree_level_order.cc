#include <memory>
#include <queue>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::queue;
using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  queue<BinaryTreeNode<int>*> q({tree.get()});
  vector<vector<int>> res;

  while (!q.empty()) {
    vector<int> lvl;
    int size = q.size();
    while (size--) {
      auto curr = q.front();
      q.pop();

      if (curr) {
        lvl.emplace_back(curr->data);
        q.emplace(curr->left.get());
        q.emplace(curr->right.get());
      }
    }
    if (!lvl.empty()) {
      res.emplace_back(lvl);
    }
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
