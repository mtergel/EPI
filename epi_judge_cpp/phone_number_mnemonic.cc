#include <memory>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::array;
using std::string;
using std::vector;

const array<string, 10> m = {
    {"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"}};


// could use unique poiner or something to
// reduce space usage
// but w/e xd
void Helper(int i, const string& phone_number, string path,
            vector<string>* res) {
  if (i == phone_number.size()) {
    res->emplace_back(path);
    return;
  }

  for (char c : m[phone_number[i] - '0']) {
    Helper(i + 1, phone_number, path + c, res);
  }
}

vector<string> PhoneMnemonic(const string& phone_number) {
  vector<string> res;
  Helper(0, phone_number, "", &res);

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         UnorderedComparator{}, param_names);
}
