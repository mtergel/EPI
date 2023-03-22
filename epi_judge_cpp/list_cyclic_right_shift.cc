#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> CyclicallyRightShiftList(shared_ptr<ListNode<int>> L,
                                                   int k) {
  if (L == nullptr) {
    return nullptr;
  }

  auto curr = L;
  int list_len = 1;

  while (curr->next) {
    curr = curr->next;
    ++list_len;
  }

  k %= list_len;  // rotate amount
  if (k == 0) {
    return L;
  }

  curr->next = L;  // make it cyclic
  int steps_req = list_len - k;

  auto iter = curr;
  while (steps_req--) {
    iter = iter->next;
  }

  auto new_head = iter->next;
  iter->next = nullptr;  // remove cycle

  return new_head;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(
      args, "list_cyclic_right_shift.cc", "list_cyclic_right_shift.tsv",
      &CyclicallyRightShiftList, DefaultComparator{}, param_names);
}
