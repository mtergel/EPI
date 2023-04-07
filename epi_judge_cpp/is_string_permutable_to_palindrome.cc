#include <algorithm>
#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;

bool CanFormPalindrome(const string& s) {
  unordered_map<char, int> m;
  for (auto& letter : s) {
    ++m[letter];
  }

  int odd_freq = 0;
  // for (auto& p : m) {
  //   if (p.second % 2) {
  //     ++odd_freq;
  //     if (odd_freq > 1) {
  //       return false;
  //     }
  //   }
  // }
  //
  // return odd_freq <= 1;

  // at most one charecter of odd count can appear once.
  return std::none_of(m.begin(), m.end(), [&odd_freq](const auto& p) {
    return (p.second % 2) && ++odd_freq > 1;
  });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
