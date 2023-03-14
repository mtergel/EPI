#include <cctype>
#include <string>

#include "test_framework/generic_test.h"
using std::isdigit;
using std::string;

string ConvertHelper(int num, int base) {
  return num == 0
             ? ""
             : ConvertHelper(num / base, base) +
                   static_cast<char>(num % base >= 10 ? 'A' + num % base - 10
                                                      : '0' + num % base);
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
  // to convert to any base
  // convert to decimal
  // then convert it desired base

  int num = 0;
  bool is_negative = num_as_string.front() == '-';
  for (int i = (is_negative ? 1 : 0); i < num_as_string.size(); ++i) {
    num = num * b1;
    if (isdigit(num_as_string[i])) {
      num += num_as_string[i] - '0';
    } else {
      num += num_as_string[i] - 'A' + 10;
    }
  }

  return (is_negative ? "-" : "") + (num == 0 ? "0" : ConvertHelper(num, b2));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
