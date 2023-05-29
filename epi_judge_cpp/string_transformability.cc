#include <queue>
#include <string>
#include <unordered_set>

#include "test_framework/generic_test.h"
using std::queue;
using std::string;
using std::unordered_set;

int TransformString(unordered_set<string> D, const string &s, const string &t) {
  if (D.find(s) == D.end()) {
    return false;
  }

  queue<string> q;
  q.push(s);
  D.erase(s);
  int res = 0;

  while (!q.empty()) {
    int size = q.size();
    while (size--) {
      auto curr = q.front();
      q.pop();

      if (curr == t) {
        return res;
      }

      for (int i = 0; i < curr.size(); ++i) {
        char prev = curr[i];
        for (char c = 'a'; c <= 'z'; ++c) {
          curr[i] = c;
          if (D.find(curr) != D.end()) {
            q.push(curr);
            D.erase(curr);
          }
        }
        curr[i] = prev;
      }
    }

    ++res;
  }

  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"D", "s", "t"};
  return GenericTestMain(args, "string_transformability.cc",
                         "string_transformability.tsv", &TransformString,
                         DefaultComparator{}, param_names);
}
