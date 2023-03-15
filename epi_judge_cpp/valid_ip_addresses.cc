#include <algorithm>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::min;
using std::stoi;
using std::string;
using std::vector;

bool isValidPart(const string& s) {
  if (s.size() > 3 || s.front() == '0' && s.size() > 1) {
    return false;
  }

  int val = stoi(s);

  return val <= 255 && val >= 0;
}

void solve(vector<string>& res, const string& s, string path, int i, int dots) {
  if (dots == 4 && i == s.size()) {
    path.pop_back();
    res.emplace_back(path);  // extra dot
  }

  if (dots > 4) {
    return;
  }

  for (int j = i; j < min(i + 3, static_cast<int>(s.length())); ++j) {
    if (isValidPart(s.substr(i, j - i + 1))) {
      solve(res, s, path + s.substr(i, j - i + 1) + '.', j + 1, dots + 1);
    }
  }

  // idk
  // for (int j = 1; j + i < s.size() && j < 4; ++j) {
  //   if (isValidPart(s.substr(i, j))) {
  //     solve(res, s, path + s.substr(i, j) + '.', i + j, dots + 1);
  //   }
  // }
}

vector<string> GetValidIpAddress(const string& s) {
  vector<string> res;
  solve(res, s, "", 0, 0);
  // for (int i = 1; i < 4 && i < s.size(); ++i) {
  //   const string first = s.substr(0, i);
  //   if (isValidPart(first)) {
  //     for (int j = 1; i + j < s.size() && j < 4; ++j) {
  //       const string second = s.substr(i, j);
  //       if (isValidPart(second)) {
  //         for (int k = 1; i + j + k < s.size() && k < 4; ++k) {
  //           const string third = s.substr(i + j, k),
  //                        fourth = s.substr(i + j + k);
  //
  //           if (isValidPart(third) && isValidPart(fourth)) {
  //             res.emplace_back(first + '.' + second + '.' + third + '.' +
  //                              fourth);
  //           }
  //         }
  //       }
  //     }
  //   }
  // }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "valid_ip_addresses.cc",
                         "valid_ip_addresses.tsv", &GetValidIpAddress,
                         UnorderedComparator{}, param_names);
}
