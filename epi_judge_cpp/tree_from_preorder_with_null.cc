#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

unique_ptr<BinaryTreeNode<int>> helper(const vector<int*>& preorder,
                                       int* root_idx) {
  int& idx = *root_idx;
  int* key = preorder[idx];
  ++idx;

  if (key == nullptr) {
    return nullptr;
  }

  auto left = helper(preorder, root_idx);
  auto right = helper(preorder, root_idx);

  return std::make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{*key, std::move(left), std::move(right)});
}

unique_ptr<BinaryTreeNode<int>> ReconstructPreorder(
    const vector<int*>& preorder) {
  int root_idx = 0;
  return helper(preorder, &root_idx);
}
unique_ptr<BinaryTreeNode<int>> ReconstructPreorderWrapper(
    TimedExecutor& executor, const vector<string>& preorder) {
  vector<int> values;
  vector<int*> ptrs;
  values.reserve(preorder.size());
  for (auto& s : preorder) {
    if (s == "null") {
      ptrs.push_back(nullptr);
    } else {
      int i = std::stoi(s);
      values.push_back(i);
      ptrs.push_back(&values.back());
    }
  }

  return executor.Run([&] { return ReconstructPreorder(ptrs); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "preorder"};
  return GenericTestMain(args, "tree_from_preorder_with_null.cc",
                         "tree_from_preorder_with_null.tsv",
                         &ReconstructPreorderWrapper, DefaultComparator{},
                         param_names);
}
