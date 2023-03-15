#include <cctype>
#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::isdigit;
using std::string;
using std::to_string;

string Decoding(const string &s) {
  string res;

  int count = 0;
  for (const char &c : s) {
    if (isdigit(c)) {
      count = count * 10 + c - '0';
    } else {
      res.append(count, c);
      count = 0;
    }
  }

  return res;
}
string Encoding(const string &s) {
  string res;

  for (int i = 0; i < s.size(); i++) {
    int count = 1;
    while (i + 1 < s.size() && s[i] == s[i + 1]) {
      ++count, ++i;
    }

    res += to_string(count) + s[i];
  }

  return res;
}
void RleTester(const string &encoded, const string &decoded) {
  if (Decoding(encoded) != decoded) {
    throw TestFailure("Decoding failed");
  }
  if (Encoding(decoded) != encoded) {
    throw TestFailure("Encoding failed");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"encoded", "decoded"};
  return GenericTestMain(args, "run_length_compression.cc",
                         "run_length_compression.tsv", &RleTester,
                         DefaultComparator{}, param_names);
}
