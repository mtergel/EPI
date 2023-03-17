#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  if (start == finish) {
    return L;
  }

  // same memory to L?
  auto dummy = make_shared<ListNode<int>>(ListNode<int>{0, L});
  auto sublist_head = dummy;

  // list indexed from 1
  int k = 1;
  while (k++ < start) {
    sublist_head = sublist_head->next;
  }

  // sublist_head right before index start node
  auto sublist_iter = sublist_head->next;
  shared_ptr<ListNode<int>> prev = nullptr;

  // reverse sublist
  while (start++ < finish + 1) {
    auto temp = sublist_iter->next;
    sublist_iter->next = prev;
    prev = sublist_iter;
    sublist_iter = temp;
  }

  // fix sublist edge poiter
  sublist_head->next->next = sublist_iter;
  sublist_head->next = prev;

  return dummy->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
