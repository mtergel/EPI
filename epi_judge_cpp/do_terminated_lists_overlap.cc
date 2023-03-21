#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

int GetLength(shared_ptr<ListNode<int>> l);
void AdvanceListByK(shared_ptr<ListNode<int>>* l, int k);

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
    shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
  int l0_len = GetLength(l0), l1_len = GetLength(l1);

  AdvanceListByK(l0_len > l1_len ? &l0 : &l1, abs(l0_len - l1_len));

  while (l0 && l1) {
    if (l0 == l1) {
      return l0;
    }

    l0 = l0->next;
    l1 = l1->next;
  }

  return nullptr;
}

int GetLength(shared_ptr<ListNode<int>> l) {
  int count = 0;
  while (l) {
    ++count;
    l = l->next;
  }
  return count;
}

void AdvanceListByK(shared_ptr<ListNode<int>>* l, int k) {
  while (*l && k--) {
    *l = (*l)->next;
  }
}

void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (l0) {
      auto i = l0;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l0 = common;
    }

    if (l1) {
      auto i = l1;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l1 = common;
    }
  }

  auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

  if (result != common) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
  return GenericTestMain(
      args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
      &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
