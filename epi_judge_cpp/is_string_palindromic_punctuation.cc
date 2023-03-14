#include <cctype>
#include <string>

#include "test_framework/generic_test.h"
using std::isalnum;
using std::string;
using std::tolower;

bool IsPalindrome(const string& s) {
  int l = 0, r = s.size() - 1;
  while (l < r) {
    while (l < r && !isalnum(s[l])) {
      ++l;
    }

    while (l < r && !isalnum(s[r])) {
      --r;
    }

    if (tolower(s[l++]) != tolower(s[r--])) {
      return false;
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
