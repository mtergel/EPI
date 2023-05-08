#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::max;
using std::vector;

struct Item {
  int weight, value;
};

int OptimumSubjectToCapacity(const vector<Item> &items, int capacity) {

  // O(C) space
  vector<int> dp(capacity + 1, 0);

  for (const auto &item : items) {
    for (int i = capacity; i >= item.weight; --i) {
      dp[i] = max(dp[i], item.value + dp[i - item.weight]);
    }
  }

  // Variant: Fractional problem
  // Greedy approach
  // Sort by ratio of profit/weight
  // Take the item with the highest ratio and add them as much as we can

  // Variant: Divide-the-spoils,
  // Backtracking?
  // one sum, other sum, current idx, items
  // helper(0, total_sum, 0, &items)

  // Variant: Divide-the-spoils, thieves have the same number of items
  // Greedy? sort them assign them

  // Variant: Vote tie? idk

  return dp[capacity];
}
namespace test_framework {
template <> struct SerializationTrait<Item> : UserSerTrait<Item, int, int> {};
} // namespace test_framework

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"items", "capacity"};
  return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
                         &OptimumSubjectToCapacity, DefaultComparator{},
                         param_names);
}
