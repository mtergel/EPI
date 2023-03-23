#include <sstream>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::invalid_argument;
using std::string;
using std::vector;
string ShortestEquivalentPath(const string& path) {
  if (path.empty()) {
    throw invalid_argument("Empty");
  }

  vector<string> stk;
  if (path.front() == '/') {
    stk.emplace_back("/");
  }

  std::stringstream ss(path);
  string token;

  while (std::getline(ss, token, '/')) {
    if (token == "..") {
      if (stk.empty() || stk.back() == "..") {
        stk.emplace_back(token);
      } else {
        if (stk.back() == "/") {
          throw invalid_argument("path error");
        }

        stk.pop_back();
      }
    } else if (token != "." && token != "") {
      stk.emplace_back(token);
    }
  }

  string res;
  if (!stk.empty()) {
    res = stk.front();

    for (int i = 1; i < stk.size(); ++i) {
      if (i == 1 && res == "/") {
        res += stk[i];
      } else {
        res += "/" + stk[i];
      }
    }
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
