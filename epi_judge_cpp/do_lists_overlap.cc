#include <set>
#include <stdexcept>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

#define main _main
#include "do_terminated_lists_overlap.cc"
#undef main
#define main __main
#include "is_list_cyclic.cc"
#undef main

int GetDistance(shared_ptr<ListNode<int>> start, shared_ptr<ListNode<int>> end);

shared_ptr<ListNode<int>> OverlappingLists(shared_ptr<ListNode<int>> l0,
                                           shared_ptr<ListNode<int>> l1) {
  // if no cyclic then just check using prev solution
  auto c0 = HasCycle(l0), c1 = HasCycle(l1);
  if (c0 == nullptr && c1 == nullptr) {
    return OverlappingNoCycleLists(l0, l1);
  }

  // if one cyclic and other one is not then no overlap
  if ((c0 && !c1) || (!c0 && c1)) {
    return nullptr;
  }

  // if both have cyclic, check if cycles are identical

  // check cycle
  auto temp = c1;
  do {
    temp = temp->next;
  } while (temp != c0 && temp != c1);

  // not in the same cycle
  if (temp != c0) {
    return nullptr;
  }

  // l0, l1 in same cycle
  int l0_len_before = GetDistance(l0, c0);
  int l1_len_before = GetDistance(l1, c1);

  // move longer to cycle
  AdvanceListByK(l0_len_before > l1_len_before ? &l0 : &l1,
                 abs(l0_len_before - l1_len_before));

  while (l0 != l1 && l0 != c0 && l1 != c1) {
    l0 = l0->next, l1 = l1->next;
  }

  // l0 == l1, overlap first occurs before cycle starts
  return l0 == l1 ? l0 : c0;
}

int GetDistance(shared_ptr<ListNode<int>> start,
                shared_ptr<ListNode<int>> end) {
  int dist = 0;
  while (start != end) {
    ++dist;
    start = start->next;
  }

  return dist;
}

void OverlappingListsWrapper(TimedExecutor& executor,
                             shared_ptr<ListNode<int>> l0,
                             shared_ptr<ListNode<int>> l1,
                             shared_ptr<ListNode<int>> common, int cycle0,
                             int cycle1) {
  if (common) {
    if (!l0) {
      l0 = common;
    } else {
      auto it = l0;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }

    if (!l1) {
      l1 = common;
    } else {
      auto it = l1;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }
  }

  if (cycle0 != -1 && l0) {
    auto last = l0;
    while (last->next) {
      last = last->next;
    }
    auto it = l0;
    while (cycle0-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  if (cycle1 != -1 && l1) {
    auto last = l1;
    while (last->next) {
      last = last->next;
    }
    auto it = l1;
    while (cycle1-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  std::set<shared_ptr<ListNode<int>>> common_nodes;
  auto it = common;
  while (it && common_nodes.count(it) == 0) {
    common_nodes.insert(it);
    it = it->next;
  }

  auto result = executor.Run([&] { return OverlappingLists(l0, l1); });

  if (!((common_nodes.empty() && result == nullptr) ||
        common_nodes.count(result) > 0)) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0",     "l1",
                                       "common",   "cycle0", "cycle1"};
  return GenericTestMain(args, "do_lists_overlap.cc", "do_lists_overlap.tsv",
                         &OverlappingListsWrapper, DefaultComparator{},
                         param_names);
}
