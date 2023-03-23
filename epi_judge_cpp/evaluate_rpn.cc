#include <sstream>
#include <stack>
#include <string>

#include "test_framework/generic_test.h"
using std::getline;
using std::stack;
using std::stoi;
using std::string;
using std::stringstream;

// "45,81,+,8,4,*,9,*,+,5720,+"   6134	45+81+8*4*9+5720
int Evaluate(const string& expression) {
  stack<int> num;
  stringstream ss(expression);
  string token;
  const char kDelimiter = ',';

  while (getline(ss, token, kDelimiter)) {
    if (token == "+" || token == "-" || token == "*" || token == "/") {
      const int y = num.top();
      num.pop();

      const int x = num.top();
      num.pop();

      switch (token.front()) {
        case '+':
          num.emplace(x + y);
          break;
        case '-':
          num.emplace(x - y);
          break;
        case '*':
          num.emplace(x * y);
          break;
        case '/':
          num.emplace(x / y);
          break;
      }

    } else {
      num.push(stoi(token));
    }
  }
  return num.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
