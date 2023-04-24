#include <climits>
#include <iterator>
#include <map>
#include <vector>

#include "test_framework/generic_test.h"
using std::min;
using std::multimap;
using std::next;
using std::vector;

int FindClosestElementsInSortedArrays(
    const vector<vector<int>> &sorted_arrays) {
  int res = INT_MAX;

  struct IterTail {
    vector<int>::const_iterator iter, tail;
  };

  // stores two iterators in each entry, one for traversing and one for to check
  // if reach end
  // multimap, sorts keys, allows duplicate keys
  // repeatedly insert, delete, find the minimum and find maximum, bst is the
  // natural choice
  multimap<int, IterTail> m;

  for (const vector<int> &a : sorted_arrays) {
    m.emplace(a.front(), IterTail{a.cbegin(), a.cend()});
  }

  while (true) {
    int min_val = m.cbegin()->first, max_val = m.crbegin()->first;

    res = min(res, max_val - min_val);

    const auto next_min = next(m.cbegin()->second.iter);
    const auto next_end = m.cbegin()->second.tail;

    // return if some array has no remaining elements
    if (next_min == next_end) {
      return res;
    }

    m.emplace(*next_min, IterTail{next_min, next_end});
    m.erase(m.cbegin());
  }

  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "minimum_distance_3_sorted_arrays.cc",
                         "minimum_distance_3_sorted_arrays.tsv",
                         &FindClosestElementsInSortedArrays,
                         DefaultComparator{}, param_names);
}
