#include "array"
#include "list_node.h"
#include "test_framework/generic_test.h"

using std::array;

shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  if (L == nullptr) {
    return L;
  }

  auto even_dummy = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  auto odd_dummy = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});

  array<shared_ptr<ListNode<int>>, 2> tails = {even_dummy, odd_dummy};
  int turn = 0;
  for (auto iter = L; iter; iter = iter->next) {
    tails[turn]->next = iter;
    tails[turn] = tails[turn]->next;

    turn ^= 1;
  }

  tails[1]->next = nullptr;
  tails[0]->next = odd_dummy->next;

  return even_dummy->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
