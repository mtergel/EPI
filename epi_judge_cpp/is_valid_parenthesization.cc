#include <stack>
#include <string>

#include "test_framework/generic_test.h"
using std::stack;
using std::string;

bool IsWellFormed(const string& s) {
  // check parenthesis lol
  stack<char> stk;
  for (auto& c : s) {
    if (c == '(' || c == '{' || c == '[') {
      stk.emplace(c);
    } else {
      if (stk.empty()) {
        return false;
      }

      if ((c == ')' && stk.top() != '(') || (c == '}' && stk.top() != '{') ||
          (c == ']' && stk.top() != '[')) {
        return false;
      }

      stk.pop();
    }
  }
  return stk.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
