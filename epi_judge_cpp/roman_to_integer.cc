#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;

int RomanToInteger(const string& s) {
  unordered_map<char, int> m = {{'I', 1},   {'V', 5},   {'X', 10},  {'L', 50},
                                {'C', 100}, {'D', 500}, {'M', 1000}};

  // right->left
  int res = m[s.back()];
  for (int i = s.size() - 2; i >= 0; --i) {
    if (m[s[i]] < m[s[i + 1]]) {
      res -= m[s[i]];
    } else {
      res += m[s[i]];
    }
  }

  // left->right
  // int res = 0;
  // for (int i = 0; i < s.size(); ++i) {
  //   switch (s[i]) {
  //     case 'I':
  //       if (i + 1 < s.size()) {
  //         if (s[i + 1] == 'V' || s[i + 1] == 'X') {
  //           res += m[s[i + 1]] - m[s[i]];
  //           ++i;
  //           break;
  //         }
  //       }
  //     case 'X':
  //       if (i + 1 < s.size()) {
  //         if (s[i + 1] == 'L' || s[i + 1] == 'C') {
  //           res += m[s[i + 1]] - m[s[i]];
  //           ++i;
  //           break;
  //         }
  //       }
  //     case 'C':
  //       if (i + 1 < s.size()) {
  //         if (s[i + 1] == 'D' || s[i + 1] == 'M') {
  //           res += m[s[i + 1]] - m[s[i]];
  //           ++i;
  //           break;
  //         }
  //       }
  //     default:
  //       res += m[s[i]];
  //       break;
  //   }
  // }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "roman_to_integer.cc", "roman_to_integer.tsv",
                         &RomanToInteger, DefaultComparator{}, param_names);
}
