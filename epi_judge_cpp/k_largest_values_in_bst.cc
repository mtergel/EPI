#include <memory>
#include <stack>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::stack;
using std::unique_ptr;
using std::vector;

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
  // k delayed pointer ?

  vector<int> res;

  stack<BstNode<int>*> stk;
  BstNode<int>* curr = tree.get();

  while ((curr || !stk.empty()) && k) {
    // go right untill we hit the largest element
    while (curr) {
      stk.push(curr);
      curr = curr->right.get();
    }

    curr = stk.top();
    stk.pop();

    res.push_back(curr->data);
    k--;

    curr = curr->left.get();
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}
