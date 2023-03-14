#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

int ReplaceAndRemove(int size, char s[]) {
  int write_index = 0;
  int a_count = 0;

  for (int i = 0; i < size; ++i) {
    // remove b by overwriting them with next char
    if (s[i] != 'b') {
      s[write_index++] = s[i];
    }

    if (s[i] == 'a') {
      ++a_count;
    }
  }

  // the back of the subarray without b
  int curr_idx = write_index - 1;

  // final of the size with a's replaced with dd's
  write_index = write_index + a_count - 1;
  const int final_size = write_index + 1;
  while (curr_idx >= 0) {
    if (s[curr_idx] == 'a') {
      s[write_index--] = 'd';
      s[write_index--] = 'd';
    } else {
      s[write_index--] = s[curr_idx];
    }
    --curr_idx;
  }

  return final_size;
}
vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
                                       const vector<string>& s) {
  std::vector<char> s_copy(s.size(), '\0');
  for (int i = 0; i < s.size(); ++i) {
    if (!s[i].empty()) {
      s_copy[i] = s[i][0];
    }
  }

  int res_size =
      executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

  vector<string> result;
  for (int i = 0; i < res_size; ++i) {
    result.emplace_back(string(1, s_copy[i]));
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "size", "s"};
  return GenericTestMain(args, "replace_and_remove.cc",
                         "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                         DefaultComparator{}, param_names);
}
