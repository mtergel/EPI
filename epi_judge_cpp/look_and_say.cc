#include <string>

#include "test_framework/generic_test.h"
using std::string;
using std::to_string;

string GetNext(const string& s);

string LookAndSay(int n) {
  string res = "1";
  for (int i = 1; i < n; ++i) {
    res = GetNext(res);
  }
  return res;
}

string GetNext(const string& s) {
  string result = "";

  for (int i = 0; i < s.size(); ++i) {
    int count = 1;
    while (i + 1 < s.size() && s[i + 1] == s[i]) {
      ++count;
      ++i;
    }
    result += to_string(count) + s[i];
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
