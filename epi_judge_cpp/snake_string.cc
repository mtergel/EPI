#include <string>

#include "test_framework/generic_test.h"
using std::string;

string SnakeString(const string& s) {
  string res = "";

  for (int i = 1; i < s.size(); i += 4) {
    res += s[i];
  }
  for (int i = 0; i < s.size(); i += 2) {
    res += s[i];
  }
  for (int i = 3; i < s.size(); i += 4) {
    res += s[i];
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "snake_string.cc", "snake_string.tsv",
                         &SnakeString, DefaultComparator{}, param_names);
}
