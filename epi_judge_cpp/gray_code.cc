#include <algorithm>
#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unordered_set;
using std::vector;

bool DiffersByOne(int x, int y) {
  int bit_diff = x ^ y;
  return bit_diff && !(bit_diff & (bit_diff - 1));
}

bool helper(vector<int> &res, unordered_set<int> &curr, int n) {
  if (res.size() == (1 << n)) {
    return DiffersByOne(res.front(), res.back());
  }

  for (int i = 0; i < n; ++i) {
    int prev = res.back();
    int candidate_next = prev ^ (1 << i);

    if (!curr.count(candidate_next)) {
      curr.emplace(candidate_next);
      res.emplace_back(candidate_next);

      if (helper(res, curr, n)) {
        return true;
      }

      curr.erase(candidate_next);
      res.pop_back();
    }
  }

  return false;
}

vector<int> GrayCode(int num_bits) {
  vector<int> res = {0};
  unordered_set<int> curr = {0};

  helper(res, curr, num_bits);

  return res;
}
bool DiffersByOneBit(int x, int y) {
  int bit_difference = x ^ y;
  return bit_difference && !(bit_difference & (bit_difference - 1));
}

void GrayCodeWrapper(TimedExecutor &executor, int num_bits) {
  vector<int> result = executor.Run([&] { return GrayCode(num_bits); });

  int expected_size = (1 << num_bits);
  if (result.size() != expected_size) {
    throw TestFailure("Length mismatch: expected " +
                      std::to_string(expected_size) + ", got " +
                      std::to_string(result.size()));
  }
  for (int i = 1; i < result.size(); i++)
    if (!DiffersByOneBit(result[i - 1], result[i])) {
      if (result[i - 1] == result[i]) {
        throw TestFailure("Two adjacent entries are equal");
      } else {
        throw TestFailure("Two adjacent entries differ by more than 1 bit");
      }
    }

  std::sort(begin(result), end(result));
  auto uniq = std::unique(begin(result), end(result));
  if (uniq != end(result)) {
    throw TestFailure("Not all entries are distinct: found " +
                      std::to_string(std::distance(uniq, end(result))) +
                      " duplicates");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_bits"};
  return GenericTestMain(args, "gray_code.cc", "gray_code.tsv",
                         &GrayCodeWrapper, DefaultComparator{}, param_names);
}
