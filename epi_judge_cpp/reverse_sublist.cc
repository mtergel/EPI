#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  if (start == finish) {
    return L;
  }

  shared_ptr<ListNode<int>> dummy =
      make_shared<ListNode<int>>(ListNode<int>{-1, L});
  auto prev = dummy;

  // go untill before start
  int k = 1;
  while (k++ < start) {
    prev = prev->next;
  }

  auto curr = prev->next;

  // prev -> forw -> curr -> next
  while (start++ < finish) {
    auto next = curr->next;
    curr->next = next->next;
    next->next = prev->next;
    prev->next = next;
  }

  return dummy->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
